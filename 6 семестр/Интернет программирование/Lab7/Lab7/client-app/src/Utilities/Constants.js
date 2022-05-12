const applicationName = 'LAB7';

const API_BASE_URL_DEVELOPMENT = 'https://localhost:7084';
const API_BASE_URL_PRODUCTION = '';

const ENDPOINTS = {
    LOGIN: 'login',
    LOGOUT: 'logout',
    REGISTER: 'register',
    GALLERY: 'gallery'
};


const development = {
    API_URL_LOGIN: `${API_BASE_URL_DEVELOPMENT}/${ENDPOINTS.LOGIN}`,
    API_URL_LOGOUT: `${API_BASE_URL_DEVELOPMENT}/${ENDPOINTS.LOGOUT}`,
    API_URL_REGISTER: `${API_BASE_URL_DEVELOPMENT}/${ENDPOINTS.REGISTER}`,
    API_URL_GALLERY: `${API_BASE_URL_DEVELOPMENT}/${ENDPOINTS.GALLERY}`
};

const production = {
    API_URL_LOGIN: `${API_BASE_URL_PRODUCTION}/${ENDPOINTS.LOGIN}`,
    API_URL_LOGOUT: `${API_BASE_URL_PRODUCTION}/${ENDPOINTS.LOGOUT}`,
    API_URL_REGISTER: `${API_BASE_URL_PRODUCTION}/${ENDPOINTS.REGISTER}`,
    API_URL_GALLERY: `${API_BASE_URL_PRODUCTION}/${ENDPOINTS.GALLERY}`,
};

const Constants = process.env.NODE_ENV === 'development' ? development : production;
export default Constants;
