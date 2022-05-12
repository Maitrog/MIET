import { Navigate, Outlet } from "react-router-dom";
import authService from "./AuthorizeService"

const ProtectedRoutes = () =>{
    const isAuthenticated = authService.isAuthenticated();
    return isAuthenticated ? <Outlet/> : <Navigate to='/Authorize' />;
}

export default ProtectedRoutes;
