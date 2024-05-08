import cv2
import sys
import numpy as np

def apply_zoom_effect(image, zoom_factor):
    height, width = image.shape[:2]
    center_x, center_y = width // 2, height // 2
    zoom = cv2.getRotationMatrix2D((center_x, center_y), 0, zoom_factor)
    return cv2.warpAffine(image, zoom, (width, height))

def add_advanced_image_display(input_video_path, output_video_path, image_paths, duration=60, fps=30):
    cap = cv2.VideoCapture(input_video_path)
    if not cap.isOpened():
        raise ValueError("Erreur lors de l'ouverture de la vid�o. V�rifiez le chemin.")

    width, height = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)), int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    out = cv2.VideoWriter(output_video_path, fourcc, fps, (width, height))

    total_frames = duration * fps
    image_change_interval = 4 * fps
    first_image_frame = 6 * fps
    image_display_duration_frames = 3 * fps
    num_images = len(image_paths)
    image_index = -1
    frame_count = 0

    current_image = None
    zoom_factor = 1.0

    while frame_count < total_frames:
        ret, frame = cap.read()
        if not ret:
            break

        if frame_count >= first_image_frame and (frame_count - first_image_frame) % image_change_interval == 0:
            image_index += 1
            if image_index < num_images:
                current_image_path = image_paths[image_index]
                if current_image_path and current_image_path != '0':
                    current_image = cv2.imread(current_image_path)
                    if current_image is not None:
                        current_image = cv2.resize(current_image, (400, 400))
                        zoom_factor = 1.0 

        if current_image is not None and frame_count - first_image_frame - image_index * image_change_interval < image_display_duration_frames:
            zoomed_image = apply_zoom_effect(current_image, zoom_factor)
            x_offset, y_offset = (width - 400) // 2, (height - 400) // 2
            frame[y_offset:y_offset+400, x_offset:x_offset+400] = zoomed_image
            zoom_factor *= 1.0005  

        out.write(frame)
        frame_count += 1

    cap.release()
    out.release()
    print("Traitement video avance termine.")

if __name__ == "__main__":
    input_video_path = sys.argv[1]
    output_video_path = sys.argv[2]
    image_paths = sys.argv[3].split(',')

    add_advanced_image_display(input_video_path, output_video_path, image_paths)
