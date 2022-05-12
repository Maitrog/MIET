import React from "react";
import { useNavigate } from "react-router-dom";
import { Container } from "reactstrap";
import authService from "./AuthorizeService";

const Home = () => {
    const navigate = useNavigate();
    
    async function onUserLogout(e){
        e.preventDefault();
        
        authService.singOut();
        navigate('/Authorize');
    } 

    return (
        <Container id="userInfo">
            <p>Добро пожаловать <span id="userName"></span>!</p>
            <input type="button" value="Выйти" id="logout" onClick={onUserLogout} />
        </Container>
    );
}

export default Home;
