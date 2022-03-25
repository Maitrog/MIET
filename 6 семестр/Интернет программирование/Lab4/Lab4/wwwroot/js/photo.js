var modal = document.getElementById('myModal');
var images = document.getElementsByClassName('myImage');

// Get the image and insert it inside the modal - use its "alt" text as a caption
for (var i = 0; i < images.length; i++) {
    var img = images[i];
    var modalImg = document.getElementById("img01");
    var captionText = document.getElementById("caption");
    img.onclick = function () {
        modal.style.display = "block";
        modalImg.src = this.src;
        modalImg.alt = this.alt;
    }

    // When the user clicks on <span> (x), close the modal
    modal.onclick = function () {
        img01.className += " out";
        setTimeout(function () {
            modal.style.display = "none";
            img01.className = "modal-content";
        }, 400);

    }
}


var _URL = window.URL || window.webkitURL;
function choosePhoto(input) {
    if (input.files && input.files[0]) {
        var width;
        var height;
        var reader = new FileReader();
        reader.onload = function (e) {
            const preview = document.getElementById("myImg");
            preview["src"] = e.target.result;
            preview["height"] = 150;
            preview["width"] = 150;
        };
        reader.readAsDataURL(input.files[0]);

        var photo = document.getElementById("userPhoto");
        if (input.files[0].size > 16777216) {
            photo.setCustomValidity('Размер файла слишком большой');
        } else if (!isValidSource(input.files[0].name)) {
            photo.setCustomValidity('Название файла содержит запрещенные слова');
        } else {
            photo.setCustomValidity('');
        }
    }
}

document.getElementById("myImg").onload = function () {
    photo = document.getElementById("userPhoto");
    if (!photo.customError && (this.naturalWidth > 800 || this.naturalHeight > 800)) {
        photo.setCustomValidity('Разрешение изображения не должно превышать 800×800');
        console.log('Разрешение изображения не должно превышать 800×800');
    }
}

function isValidSource(path) {
    if (path.toLowerCase().includes("script")) {
        return false;
    }
    if (path.toLowerCase().includes("http")) {
        return false;
    }
    if (path.toLowerCase().includes("select")) {
        return false;
    }
    if (path.toLowerCase().includes("union")) {
        return false;
    }
    if (path.toLowerCase().includes("update")) {
        return false;
    }
    if (path.toLowerCase().includes("exe")) {
        return false;
    }
    if (path.toLowerCase().includes("exec")) {
        return false;
    }
    if (path.toLowerCase().includes("insert")) {
        return false;
    }
    if (path.toLowerCase().includes("tmp")) {
        return false;
    }
    return true;
}