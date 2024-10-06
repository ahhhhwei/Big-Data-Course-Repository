import cv2
import numpy as np
import matplotlib.pyplot as plt

# Load the image
image_path = 'smog.jpg'  
image = cv2.imread(image_path)
if image is None:
    print(f"Image not loaded correctly, please check the path: {image_path}")
else:
    # Convert BGR image to RGB for displaying
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Initialize ORB (Oriented FAST and Rotated BRIEF) detector
    orb = cv2.ORB_create()
    # Detect keypoints using ORB
    keypoints_orb, descriptors_orb = orb.detectAndCompute(image, None)
    # Draw keypoints on the image
    image_orb = cv2.drawKeypoints(image_rgb, keypoints_orb, None, color=(255, 0, 0), flags=0)

    # Initialize FAST (Features from Accelerated Segment Test) detector
    fast = cv2.FastFeatureDetector_create()
    # Detect keypoints using FAST
    keypoints_fast = fast.detect(image, None)
    # Draw keypoints on the image
    image_fast = cv2.drawKeypoints(image_rgb, keypoints_fast, None, color=(255, 0, 0), flags=0)

    # Display the original and processed images side by side
    plt.figure(figsize=(15, 5))
    plt.subplot(1, 3, 1), plt.imshow(image_rgb), plt.title('original_graph')
    plt.xticks([]), plt.yticks([])
    plt.subplot(1, 3, 2), plt.imshow(image_orb), plt.title('ORB')
    plt.xticks([]), plt.yticks([])
    plt.subplot(1, 3, 3), plt.imshow(image_fast), plt.title('FAST')
    plt.xticks([]), plt.yticks([])

    plt.show()