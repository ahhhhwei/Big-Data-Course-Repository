import dlib
import cv2
import numpy as np
import moviepy.editor as mpy

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("models/face_landmarks.dat")

def draw_rectangle(image,location): #finds and draws rectangles on image
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    rectangles = detector(gray) #list of rectangles containing the faces. Represented as xy coordinates.
    if len(rectangles) == 1: #Check whether there is only one rectangle
        tlx = rectangles[0].tl_corner().x #top left x value
        tly = rectangles[0].tl_corner().y #top left y value
        bly = rectangles[0].bl_corner().y #bottom left y value
        brx = rectangles[0].br_corner().x #bottom right x value
        green = [0,255,0] #RGB value of green color
        image[tly,tlx:brx] = green #draw top horizontal green line
        image[bly,tlx:brx] = green #draw bottom horizontal green line
        image[tly:bly,tlx] = green #draw left vertical green line
        image[tly:bly,brx] = green #draw right vertical green line
        #I used above 4 line for drawing rectangle but below cv2.rectangle function can be used also.
        #cv2.rectangle(image, (tlx, tly), (brx, bly), (0, 255, 0), 2)
        cv2.imwrite(location, image) #Write image on specified place with "location"

def paint_landmark_points(image,landmarks = None): #finds landmarks and paints them on image
    if landmarks is None: #If image includes human
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        rectangles = detector(gray) #list of rectangles containing the faces. Represented as xy coordinates.
        points = predictor(gray, rectangles[0])
        for i in range(68):
            x = points.part(i).x
            y = points.part(i).y
            image[y-2:y+3,x-2:x+3] = [0,255,0] #paint a point with green color
    else: #If image includes animal
        for i in range(68):
            x = landmarks[i][0]
            y = landmarks[i][1]
            image[y-2:y+3,x-2:x+3] = [0,255,0] #paint a point with green color
    return image

def draw_triangles(img, triangles, im_name):  # Draws triangles on image
    location = "outputs\\part2_with_triangles_"
    image = np.copy(img)  # Copy image in order to keep original image unchanged
    color = [0, 255, 0]
    for triangle in triangles:
        p1 = (int(triangle[0]), int(triangle[1]))
        p2 = (int(triangle[2]), int(triangle[3]))
        p3 = (int(triangle[4]), int(triangle[5]))
        cv2.line(image, p1, p2, color, 1)  # Draws one edge of triangle
        cv2.line(image, p1, p3, color, 1)  # Draws one edge of triangle
        cv2.line(image, p2, p3, color, 1)  # Draws one edge of triangle
    cv2.imwrite(location + im_name, image)  # Write image with triangles


def get_id(x, y, landmarks,im_shape):  # Returns ID of given point (x,y), 8 other points mapped as (-1,-2,-3,-4,-5,-6,-7,-8)
    for i in range(len(landmarks)):
        if x == landmarks[i].x and y == landmarks[i].y:  # If (x,y) is on image
            return i
        elif x == 0 and y == 0:  # If (x,y) is top left corner
            return -1
        elif x == 0 and y == im_shape[1] / 2:  # If (x,y) is top center point
            return -2
        elif x == 0 and y == im_shape[1] - 1:  # If (x,y) is top right corner
            return -3
        elif x == im_shape[0] / 2 and y == 0:  # If (x,y) is left center point
            return -4
        elif x == im_shape[0] - 1 and y == 0:  # If (x,y) is bottom left corner
            return -5
        elif x == im_shape[0] - 1 and y == im_shape[1] / 2:  # If (x,y) is bottom center point
            return -6
        elif x == im_shape[0] - 1 and y == im_shape[1] - 1:  # If (x,y) is bottom right corner
            return -7
        elif x == im_shape[0] / 2 and y == im_shape[1] - 1:  # If (x,y) is right center point
            return -8


def create_triangles(triangles, ids, im_shape, points,p_animal=False):  # Create triangles of second image according to IDs of first image
    for i in range(len(ids)):
        triangles.append([])
        for j in range(len(ids[i])):
            if ids[i][j] == -1:  # If (x,y) is top left corner
                triangles[i].append(0)
                triangles[i].append(0)
            elif ids[i][j] == -2:  # If (x,y) is top center point
                triangles[i].append(0)
                triangles[i].append(int(im_shape[1] / 2))
            elif ids[i][j] == -3:  # If (x,y) is top right corner
                triangles[i].append(0)
                triangles[i].append(int(im_shape[1] - 1))
            elif ids[i][j] == -4:  # If (x,y) is left center point
                triangles[i].append(int(im_shape[0] / 2))
                triangles[i].append(0)
            elif ids[i][j] == -5:  # If (x,y) is bottom left corner
                triangles[i].append(int(im_shape[0] - 1))
                triangles[i].append(0)
            elif ids[i][j] == -6:  # If (x,y) is bottom center point
                triangles[i].append(int(im_shape[0] - 1))
                triangles[i].append(int(im_shape[1] / 2))
            elif ids[i][j] == -7:  # If (x,y) is bottom right corner
                triangles[i].append(int(im_shape[0] - 1))
                triangles[i].append(int(im_shape[1] - 1))
            elif ids[i][j] == -8:  # If (x,y) is right center point
                triangles[i].append(int(im_shape[0] / 2))
                triangles[i].append(int(im_shape[1] - 1))
            elif not p_animal:  # If human landmark data is used
                triangles[i].append(int(points.part(ids[i][j]).x))
                triangles[i].append(int(points.part(ids[i][j]).y))
            elif p_animal:  # If given animal landmark data is used
                triangles[i].append(int(points[ids[i][j]][0]))
                triangles[i].append(int(points[ids[i][j]][1]))


def get_two_triangles(im1, im2, o1, o2, animal_points=None):  # Returns images and their triangles lists for morphing
    # image = cv2.imread(im1, cv2.IMREAD_COLOR)
    image = im1
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    rectangles = detector(gray)  # list of rectangles containing the faces. Represented as xy coordinates.
    points = predictor(gray, rectangles[0])
    subdiv = cv2.Subdiv2D((0, 0, image.shape[0], image.shape[1]))

    landmarks = []  # Landmarks of source image
    for i in range(68):
        landmarks.append(points.part(i))
        subdiv.insert((points.part(i).x, points.part(i).y))
    subdiv.insert((0, 0))  # top left corner --> -1
    subdiv.insert((0, image.shape[1] / 2))  # top center point --> -2
    subdiv.insert((0, image.shape[1] - 1))  # top right corner --> -3
    subdiv.insert((image.shape[0] / 2, 0))  # left center point --> -4
    subdiv.insert((image.shape[0] - 1, 0))  # bottom left corner --> -5
    subdiv.insert((image.shape[0] - 1, image.shape[1] / 2))  # bottom center point --> -6
    subdiv.insert((image.shape[0] - 1, image.shape[1] - 1))  # bottom right corner --> -7
    subdiv.insert((image.shape[0] / 2, image.shape[1] - 1))  # right center point --> -8
    triangles1 = subdiv.getTriangleList()
    draw_triangles(image, triangles1, o1)  # Draws triangles on image. "o1" is output image name.

    new_triangle_ids = []  # IDs of triangles of first image's corner points
    for i in range(len(triangles1)):
        new_triangle_ids.append([])
        for j in range(int(len(triangles1[i]) / 2)):
            id = get_id(triangles1[i][2 * j], triangles1[i][2 * j + 1], landmarks, image.shape)
            new_triangle_ids[i].append(id)

    image2 = cv2.imread(im2, cv2.IMREAD_COLOR)
    triangles2 = []
    if animal_points is None:  # If given human landmark data is used
        gray = cv2.cvtColor(image2, cv2.COLOR_BGR2GRAY)
        rectangles = detector(gray)  # list of rectangles containing the faces. Represented as xy coordinates.
        points2 = predictor(gray, rectangles[0])
        create_triangles(triangles2, new_triangle_ids, image2.shape, points2)
    else:  # If animal landmark data is used
        create_triangles(triangles2, new_triangle_ids, image2.shape, animal_points, True)
    triangles2 = np.array(triangles2)
    draw_triangles(image2, triangles2, o2)  # Draws triangles on image2. "o2" is output image name.

    return image, image2, triangles1, triangles2


def make_homogeneous(triangle):
    homogeneous = np.array([triangle[::2], triangle[1::2], [1, 1, 1]])  # (C)
    return homogeneous


def calc_transform(triangle1, triangle2):
    source = make_homogeneous(triangle1).T
    target = triangle2
    Mtx = np.array([np.concatenate((source[0], np.zeros(3))),
                    np.concatenate((np.zeros(3), source[0])),
                    np.concatenate((source[1], np.zeros(3))),
                    np.concatenate((np.zeros(3), source[1])),
                    np.concatenate((source[2], np.zeros(3))),
                    np.concatenate((np.zeros(3), source[2]))])  # (D)
    coefs = np.matmul(np.linalg.pinv(Mtx), target)  # (E)
    Transform = np.array([coefs[:3], coefs[3:], [0, 0, 1]])  # (F)
    return Transform


def vectorised_Bilinear(coordinates, target_img, size):
    coordinates[0] = np.clip(coordinates[0], 0, size[0] - 1)
    coordinates[1] = np.clip(coordinates[1], 0, size[1] - 1)
    lower = np.floor(coordinates).astype(np.uint32)
    upper = np.ceil(coordinates).astype(np.uint32)

    error = coordinates - lower
    resindual = 1 - error

    top_left = np.multiply(np.multiply(resindual[0], resindual[1]).reshape(
        coordinates.shape[1], 1), target_img[lower[0], lower[1], :])
    top_right = np.multiply(np.multiply(resindual[0], error[1]).reshape(
        coordinates.shape[1], 1), target_img[lower[0], upper[1], :])
    bot_left = np.multiply(np.multiply(error[0], resindual[1]).reshape(
        coordinates.shape[1], 1), target_img[upper[0], lower[1], :])
    bot_right = np.multiply(np.multiply(error[0], error[1]).reshape(
        coordinates.shape[1], 1), target_img[upper[0], upper[1], :])  # (G)

    return np.uint8(np.round(top_left + top_right + bot_left + bot_right))  # (H)


def image_morph(image1, image2, triangles1, triangles2, transforms, t):
    inter_image_1 = np.zeros(image1.shape).astype(np.uint8)
    inter_image_2 = np.zeros(image2.shape).astype(np.uint8)
    for i in range(len(transforms)):
        homo_inter_tri = (1 - t) * make_homogeneous(triangles1[i]) + t * make_homogeneous(triangles2[i])  # (I)
        polygon_mask = np.zeros(image1.shape[:2], dtype=np.uint8)
        cv2.fillPoly(polygon_mask, [np.int32(np.round(homo_inter_tri[1::-1, :].T))], color=255)  # (J)

        seg = np.where(polygon_mask == 255)  # (K)

        mask_points = np.vstack((seg[0], seg[1], np.ones(len(seg[0]))))  # (L)

        inter_tri = homo_inter_tri[:2].flatten(order="F")  # (M)

        inter_to_img1 = calc_transform(inter_tri, triangles1[i])
        inter_to_img2 = calc_transform(inter_tri, triangles2[i])

        mapped_to_img1 = np.matmul(inter_to_img1, mask_points)[:-1]  # (N)
        mapped_to_img2 = np.matmul(inter_to_img2, mask_points)[:-1]

        inter_image_1[seg[0], seg[1], :] = vectorised_Bilinear(mapped_to_img1, image1, inter_image_1.shape)  # (O)
        inter_image_2[seg[0], seg[1], :] = vectorised_Bilinear(mapped_to_img2, image2, inter_image_2.shape)

    result = (1 - t) * inter_image_1 + t * inter_image_2  # (P)

    return result.astype(np.uint8)


def write_videos(img1_triangles, img2_triangles, image, image2,location):  # Holds morphed images on list and writes them as video clip.
    img1_triangles = img1_triangles[:, [1, 0, 3, 2, 5, 4]]
    img2_triangles = img2_triangles[:, [1, 0, 3, 2, 5, 4]]

    Transforms = np.zeros((len(img1_triangles), 3, 3))
    for i in range(len(img1_triangles)):
        source = img1_triangles[i]
        target = img2_triangles[i]
        Transforms[i] = calc_transform(source, target)  # (A)

    morphs = []
    for t in np.arange(0, 1.0001, 0.02):  # (B)
        # print("processing:\t", t * 100, "%")
        morphs.append(image_morph(image, image2, img1_triangles, img2_triangles, Transforms, t)[:, :, ::-1])

    clip = mpy.ImageSequenceClip(morphs, fps=25)
    clip.write_videofile(location, codec='libx264')
    clip.close()
