% =========================================================
% Vision-Based Manipulation - Task 2
% Description: Identifies target coordinates via HSV thresholding
% =========================================================
clc; clear; close all;

vidObj = webcam;
disp('--> Video stream initialized.');

figure('Name', 'Vision Tracking System');

while true
    % Acquire and scale frame
    currentFrame = snapshot(vidObj);
    currentFrame = imresize(currentFrame, [480 640]);

    % Color space conversion to HSV
    frameHSV = rgb2hsv(currentFrame);
    hue = frameHSV(:,:,1);
    sat = frameHSV(:,:,2);
    val = frameHSV(:,:,3);

    % Isolate target hues (Orange tracking)
    targetFilter = (hue > 0.02 & hue < 0.10) & (sat > 0.4) & (val > 0.4);
    
    % Morphological operations
    targetFilter = bwareaopen(targetFilter, 500);
    targetFilter = imfill(targetFilter, 'holes');

    % Extract blob metrics
    blobMetrics = regionprops(targetFilter, 'BoundingBox', 'Centroid', 'Area');

    imshow(currentFrame);
    hold on;

    for i = 1:length(blobMetrics)
        if blobMetrics(i).Area > 1000
            bBox = blobMetrics(i).BoundingBox;
            centerPt = blobMetrics(i).Centroid;

            % Render UI tracking elements
            rectangle('Position', bBox, 'EdgeColor', 'yellow', 'LineWidth', 2.5);
            plot(centerPt(1), centerPt(2), 'bo', 'MarkerSize', 8, 'LineWidth', 2);
            text(centerPt(1), centerPt(2)-25, ...
                sprintf('X:%.0f, Y:%.0f', centerPt(1), centerPt(2)), ...
                'Color', 'cyan', 'FontSize', 11, 'FontWeight', 'bold');

            % Terminal logs
            fprintf('\n--- Target Lock ---\n');
            fprintf('Pos X: %.0f | Pos Y: %.0f\n', centerPt(1), centerPt(2));

            % -----------------------------------------------------
            % Decision Matrix for Kinematics
            % -----------------------------------------------------
            if centerPt(1) < 220
                disp('Action: Pan Left');
            elseif centerPt(1) > 420
                disp('Action: Pan Right');
            else
                disp('Action: X-Axis Aligned');
            end

            if centerPt(2) < 160
                disp('Action: Tilt Forward');
            elseif centerPt(2) > 320
                disp('Action: Tilt Backward');
            else
                disp('Action: Ready to Grasp');
            end
        end
    end
    
    hold off;
    drawnow;
end

% Cleanup routine
clear vidObj;
disp('--> System Shutdown.');
