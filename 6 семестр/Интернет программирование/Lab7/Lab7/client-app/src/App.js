import React, { Component } from "react";
import { Route, Routes } from "react-router";
import Home from "./Components/Home";
import AuthorizationForm from "./Components/AuthorizationForm";
import authService from "./Components/AuthorizeService";
import ProtectedRoutes from "./Components/ProtectedRoute";
import RegistrationForm from "./Components/RegistrationForm";
import Gallery from "./Components/Gallery";

export default class App extends Component {
    static displayName = App.name;
    constructor(props) {
        super(props);
        this.state = { authenticated: false };
    }

    componentDidMount() {
        this._subscription = authService.subscribe(() => this.authenticationChanged());
        this.populateAuthenticationState();
    }

    componentWillUnmount() {
        authService.unsubscribe(this._subscription);
    }

    render() {
        return (
            <Routes>
                <Route path='/Authorize' element={<AuthorizationForm />} />
                <Route path='/Register' element={<RegistrationForm />} />
                <Route element={<ProtectedRoutes />}>
                    <Route exact path='/' element={<Home />} />
                    <Route exact path='/Home' element={<Home />} />
                    <Route path='/Gallery' element={<Gallery />} />
                </Route>
            </Routes>
        );
    }

    async populateAuthenticationState() {
        const authenticated = await authService.isAuthenticated();
        this.setState({ authenticated: authenticated });
    }

    async authenticationChanged() {
        this.setState({ authenticated: false });
        await this.populateAuthenticationState();
    }
}
