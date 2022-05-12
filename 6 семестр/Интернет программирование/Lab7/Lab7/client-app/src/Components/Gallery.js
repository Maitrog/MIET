import axios from "axios";
import { useEffect, useState } from "react";
import Constants from "../Utilities/Constants";
import "./gallery.css";

export default function Gallery() {
    const [mounted, setMounted] = useState(false)
    const [file, setFile] = useState();
    const [image, setImage] = useState();
    const [imageURL, setImageURL] = useState();
    const [galleryURLs, setGalleryURLs] = useState();

    if (!mounted) {
        loadImage();
    }

    useEffect(() => {
        setMounted(true);
        if (!!!image) return;
        const newImageURL = URL.createObjectURL(image);
        setImageURL(newImageURL);
        setImage(null);
    })

    function isValidSource(path) {
        const blockedWords = ["script", "http", "select", "union", "update", "exe", "exec", "insert", "tmp"];
        blockedWords.map(word => {
            if (path.toLowerCase().includes(word)) {
                return false;
            }
        })
        return true;
    }

    function onImageChange(e) {
        setImage(e.target.files[0]);
        setFile(e.target.files[0]);

        const photo = e.target.files[0];
        if (photo.size > 1567897) {
            e.target.setCustomValidity('Размер файла слишком большой');
        } else if (!isValidSource(photo.name)) {
            e.target.setCustomValidity('Название файла содержит запрещенные слова');
        } else if (photo.naturalWidth > 800 || photo.naturalHeight > 800) {
            photo.setCustomValidity('Разрешение изображения не должно превышать 800×800');
        } else {
            e.target.setCustomValidity('');
        }
    }

    async function getAllImages() {
        const response = await fetch(Constants.API_URL_GALLERY, {
            method: 'GET',
            credentials: 'include',
            headers: {
                "Accept": "application/json",
                "Content-Type": "application/json",
                "Allow-Credentials": "true"
            }
        });

        if (response.ok === true) {
            const data = await response.json();
            return data;
        }
        else {
            console.log("Status: ", response.status);
        }
    }

    async function uploadImage() {
        const formData = new FormData();
        formData.append("name", file.name);
        formData.append("file", file);

        const config = {
            credentials: 'include',
            headers: {
                "Accept": "multipart/form-data",
                "Content-Type": 'multipart/form-data',
                "Allow-Credentials": "true"
            },
        }
        const response = await axios.post(Constants.API_URL_GALLERY, formData, config)
        if (response.status != 200) {
            console.log("Status: ", response.status);
        }
    }
    async function loadImage() {
        const data = await getAllImages();
        const newGalleryURLs = [];
        data.map(url => newGalleryURLs.push(`${Constants.API_URL_GALLERY}/${url}`));
        setGalleryURLs(newGalleryURLs);
    }
    async function onUploadImage(e) {
        e.preventDefault();

        await uploadImage();
        await loadImage();
    }

    function onClickImage(e){
        var modal = document.getElementById('myModal');
        var modalImg = document.getElementById("img01");
        modal.style.display = "block";
        modalImg.src = e.target.src;
        modalImg.alt = e.target.alt;
    }

    function onClickModal(e){
        var modal = document.getElementById('myModal');
        e.target.className += " out";
        setTimeout(function () {
            modal.style.display = "none";
            e.target.className = "modal-content";
        }, 400);
    }

    return (
        <div>
            <div id="loadPhoto">
                <form method="POST" onSubmit={onUploadImage}>
                    <fieldset>
                        <legend>Отправка файла</legend>
                        <p>
                            <label htmlFor="userPhoto">Файл<em>*</em></label>
                            <input type="file" className="form-control" name="userPhoto" id="userPhoto"
                                onChange={onImageChange} accept=".png, .jpg, .jpeg, .bmp" /><br />
                        </p>
                        <img id="myImg" className="myImage" src={imageURL} height="150" onClick={onClickImage} />
                        <div id="myModal" className="modal">
                            <img className="modal-content" id="img01" onClick={onClickModal} />
                        </div>
                    </fieldset>
                    <p><input type="submit" className="btn btn-dark my-1" id="submit" value="Отправить" /></p>
                </form>
            </div>

            {!!galleryURLs && galleryURLs.map(url => <img height="150" src={url} onClick={onClickImage} ></img>)}
        </div>
    );
}


