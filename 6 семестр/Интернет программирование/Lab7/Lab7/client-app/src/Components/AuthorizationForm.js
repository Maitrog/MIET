import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import authService from "./AuthorizeService";

const AuthorizationForm = () => {
    const initialFormData = Object.freeze({
        login: '',
        password: '',
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

    async function onUserLogin(e) {
        e.preventDefault();

        let user = JSON.stringify(formData);
        await authService.singIn(user);
        navigate('/Home');
    };

    function redirect(e){
        e.preventDefault();
        navigate('/Register');
    }

    return (
        <form>
            <div className="px-3" id="loginForm">
                <h3 className="">Вход на сайт</h3>
                <div className="form-group col-auto">
                    <label>Введите логин</label><br />
                    <input value={formData.login} className="form-control" placeholder="Логин" type="text" id="login" name="login" onChange={handleChange} />
                </div>
                <div className="form-group col-auto">
                    <label>Введите пароль</label><br />
                    <input value={formData.password} className="form-control" placeholder="Пароль" type="password" id="password" name="password" onChange={handleChange} />
                </div>
                <div className="col-auto">
                    <input className="btn btn-dark my-1" type="submit" id="submitLogin" value="Логин" onClick={onUserLogin} />
                </div>
                <input className="btn btn-secondary" type="button" value="Регистрация" id="register" onClick={redirect} />
            </div>
        </form>

    );
}

export default AuthorizationForm;
