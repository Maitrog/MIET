import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import Constants from "../Utilities/Constants";

const RegistrationForm = () => {
    const initialFormData = Object.freeze({
        Login: '',
        Password: '',
    });
    const [formData, setFormData] = useState(initialFormData);
    const navigate = useNavigate();

    function handleChange(e) {
        setFormData(
            {
                ...formData,
                [e.target.name]: e.target.value
            }
        );
    };

    async function onUserRegister(e) {
        e.preventDefault();
        const response = await fetch(Constants.API_URL_REGISTER, {
            method: "POST",
            credentials: 'include',
            headers: {
                "Accept": "application/json",
                "Content-Type": "application/json",
                "Allow-Credentials": "true"
            },
            body: JSON.stringify(formData)
        });

        if (response.ok) {
            alert("Успешная регистрация");
            navigate('/Authorize');
        }
        else {
            alert("Такой логин уже существует");
        }
    };

    function redirect(e){
        e.preventDefault();
        navigate('/Authorize');
    }

    return (
        <form>
            <div className="px-3" id="loginForm">
                <h3 className="">Регистрация</h3>
                <div className="form-group col-auto">
                    <label>Введите логин</label><br />
                    <input value={formData.login} className="form-control" placeholder="Логин" type="text" id="login" name="login" onChange={handleChange} />
                </div>
                <div className="form-group col-auto">
                    <label>Введите пароль</label><br />
                    <input value={formData.password} className="form-control" placeholder="Пароль" type="password" id="password" name="password" onChange={handleChange} />
                </div>
                <div className="col-auto">
                    <input className="btn btn-dark my-1" type="submit" value="Регистрация" id="register" onClick={onUserRegister} />
                </div>
                <input className="btn btn-secondary" type="button" id="submitLogin" value="Логин" onClick={redirect} />
            </div>
        </form>

    );
}

export default RegistrationForm;
