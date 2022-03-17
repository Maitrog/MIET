$(document).ready(function () {
    jQuery.validator.messages.userText = "Invalid symbols";
    jQuery.validator.messages.checkbox = "Wrong choose";
    jQuery.validator.messages.radio = "Wrong radio";

    jQuery.validator.addMethod('userText', function (userText, element) {
        return this.optional(element) || validateText(userText);
    }, 'Invalid symbols: "@#$%^"');

    jQuery.validator.addMethod("checkbox", function () {
        var selected = new Array();

        $("#checkBox1").filter(":checked").each(function () {
            selected.push(this.value);
        });
        $("#checkBox3").filter(":checked").each(function () {
            selected.push(this.value);
        });
        if (selected.length == 2) {
            return true;
        }
        return false;
    }, "Error: must select 1 and 3");

    jQuery.validator.addMethod('radio', function () {
        var radio = $('input[name="radio"]:checked').val();
        return validateRadioButton(radio);
    }, "Wrong radio");

    $.validator.setDefaults({
        submitHandler: function () {
            alert("submitted!");
        }
    });
    $().ready(function () {

        $('#myForm').validate({
            rules: {
                userText: {
                    required: true,
                    userText: true
                },
                checkbox: {
                    required: true,
                    checkbox: true
                },
                radio: {
                    required: true,
                    radio: true
                }
            },
            messages: {
                name: {
                    userText: "Invalid symbol"
                },
                checkbox: {
                    required: "Checkbox is required",
                    checkbox: "Needed 1 and 3"
                },
                radio: {
                    required: "Radio is required",
                    radio:"Needed 3"
                }
            }
        });
    });
});
//const form = document.getElementsByTagName("form")[0];

//const userText = document.getElementById("userText");
//const checkBoxes = document.getElementsByName("checkbox");
//const radioButtons = document.getElementsByName("radio");

//userText.addEventListener("input", function (event) {
//    if (!validateText(userText.value)) {
//        userText.setCustomValidity('Invalid symbols: "@#$%^"');
//    } else {
//        userText.setCustomValidity("");
//    }
//});

//form.addEventListener("submit", function (event) {
//    if (!validateText(userText.value) || !validateCheckBoxes(checkBoxes) || validateRadioButtons(radioButtons) !== "3") {
//        event.preventDefault();
//    }
//})

function validateText(text) {
    if (text.includes("$")) {
        return false;
    }
    if (text.includes("%")) {
        return false;
    }
    if (text.includes("#")) {
        return false;
    }
    if (text.includes("@")) {
        return false;
    }
    if (text.includes("^")) {
        return false;
    }
    return true;
}

function validateCheckBoxes(chekBoxes) {
    if (checkBoxes[0].checked && checkBoxes[2].checked)
        return true;
    return false;
}

function validateRadioButton(value) {
    return value === "3";
}

function validateRadioButtons(radioButtons) {
    for (var i = 0; i < radioButtons.length; i++) {
        if (radioButtons[i].checked) {
            return radioButtons[i].value;
        }
    }
}