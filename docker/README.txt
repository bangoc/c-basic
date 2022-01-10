Có thể chạy docker ở chế độ tương tác và chia sẻ thư mục với máy chủ
với lệnh sau (lưu ý thay thế các tham số với giá trị thực trong môi trường của bạn, ví dụ $(image_id)=>097d25218519, v.v..)

docker run -it -u bangoc -w ~ --mount type=bind,source="$(pwd)",target=/home/bangoc/shared $(image_id)