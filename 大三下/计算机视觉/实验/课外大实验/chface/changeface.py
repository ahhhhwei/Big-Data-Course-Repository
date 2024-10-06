import os
import numpy as np
import cv2

class ChangeFace:
    def load_face_images(folder_path):
        return [os.path.join(folder_path, f) for f in os.listdir(folder_path) if f.endswith(('.png', '.jpg'))]

    def get_face_landmarks(image, face_detector, shape_predictor):
        dets = face_detector(image, 1)
        if len(dets) == 0:
            print("No faces found.")
            return None
        shape = shape_predictor(image, dets[0])
        return np.array([[p.x, p.y] for p in shape.parts()])

    def get_image_size(image):
        return image.shape[0], image.shape[1]

    def get_face_mask(image_size, face_landmarks):
        mask = np.zeros(image_size, dtype=np.uint8)
        points = np.concatenate([face_landmarks[0:16], face_landmarks[26:17:-1]])
        cv2.fillPoly(img=mask, pts=[points], color=255)
        return mask

    def get_affine_image(image1, image2, face_landmarks1, face_landmarks2):
        three_points_index = [18, 8, 25]
        M = cv2.getAffineTransform(face_landmarks1[three_points_index].astype(np.float32),
                                face_landmarks2[three_points_index].astype(np.float32))
        dsize = (image2.shape[1], image2.shape[0])
        return cv2.warpAffine(image1, M, dsize).astype(np.uint8)

    def get_mask_center_point(image_mask):
        image_mask_index = np.argwhere(image_mask > 0)
        minxy = np.min(image_mask_index, axis=0)
        maxxy = np.max(image_mask_index, axis=0)
        return ((maxxy[1] + minxy[1]) // 2, (maxxy[0] + minxy[0]) // 2)

    def get_mask_union(mask1, mask2):
        mask = np.minimum(mask1, mask2)
        blurred_mask = cv2.blur((mask == 255) * 255, (5, 5)).astype(np.uint8)
        return cv2.blur(blurred_mask, (3, 3)).astype(np.uint8)

    def skin_color_adjustment(im1, im2, mask=None):
        if mask is None:
            im1_ksize = 55
            im2_ksize = 55
            im1_factor = cv2.GaussianBlur(im1, (im1_ksize, im1_ksize), 0).astype(float)
            im2_factor = cv2.GaussianBlur(im2, (im2_ksize, im2_ksize), 0).astype(float)
        else:
            im1_face_image = cv2.bitwise_and(im1, im1, mask=mask)
            im2_face_image = cv2.bitwise_and(im2, im2, mask=mask)
            im1_factor = np.mean(im1_face_image, axis=(0, 1))
            im2_factor = np.mean(im2_face_image, axis=(0, 1))
        
        im1 = np.clip((im1.astype(float) * im2_factor / np.clip(im1_factor, 1e-6, None)), 0, 255).astype(np.uint8)
        return im1
