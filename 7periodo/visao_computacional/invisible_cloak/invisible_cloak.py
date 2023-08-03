# DataFlair Invisible Cloak project using OpenCV
import cv2
import time
import numpy as np
cap = cv2.VideoCapture(0)

# Save the first frame before the continuous capture starts
_, background = cap.read()
time.sleep(2)
_, background = cap.read()

while cap.isOpen():
  # Update frames while reading from camera
  _, frame = cap.read()

  # Convert Image to Image HSV
  hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

  # Defining lower and upper bound HSV values
  lower_bound = np.array([50, 80, 50])
  upper_bound = np.array([90, 255, 255])

  # Defining mask for color detection
  mask = cv2.inRange(hsv, lower_bound, upper_bound)

  # Apply the mask into the background so that the cloak is created
  cloak = cv2.bitwise_and(background, background, mask=mask)

  # crate inverse
  inverse_mask = None
  cv2.invert(cloak, inverse_mask)

  # Apply the inverse
  current_background = cv2.

  combined = cv2.add(cloak, current_background)

  open_kernel = np.ones((5, 5), np.uint8)
  close_kernel = np.ones((7, 7), np.uint8)
  dilation_kernel = np.ones((10, 10), np.uint8)