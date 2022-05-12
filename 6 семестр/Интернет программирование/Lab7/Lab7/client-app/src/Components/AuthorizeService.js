import Constants from "../Utilities/Constants";

class AuthorizeService {

    constructor() {
        this._callbacks = [];
        this._nextSubscriptionId = 0;
        this._user = null;
        this._isAuthenticated = false;
    }

    isAuthenticated() {
        return localStorage.getItem('authenticated') === "true";
    }
    async singIn(user) {
        const response = await fetch(Constants.API_URL_LOGIN, {
            method: "POST",
            credentials: 'include',
            headers: {
                "Accept": "application/json",
                "Content-Type": "application/json",
                "Allow-Credentials": "true"
            },
            body: user
        });

        if (response.ok === true) {
            const data = await response.json();
            const user = { username: data.username };
            this.updateState(user);
        }
        else
            console.log("Status: ", response.status);
    }

    async singOut() {
        const response = await fetch(Constants.API_URL_LOGOUT, {
            method: "POST",
            credentials: 'include',
            headers: {
                "Accept": "application/json",
                "Content-Type": "application/json",
                "Allow-Credentials": "true"
            }
        });

        if (response.ok === true) {
            this.updateState(null);
        }

        if (response.ok !== true) {
            console.log("Status: ", response.status);
        }
    }

    updateState(user) {
        this._user = user;
        this._isAuthenticated = !!this._user && !!this._user.username;
        localStorage.setItem('authenticated', this._isAuthenticated);
        this.notifySubscribers();
    }

    subscribe(callback) {
        this._callbacks.push({ callback, subscription: this._nextSubscriptionId++ });
        return this._nextSubscriptionId - 1;
    }

    unsubscribe(subscriptionId) {
        const subscriptionIndex = this._callbacks
            .map((element, index) => element.subscription === subscriptionId ? { found: true, index } : { found: false })
            .filter(element => element.found === true);
        if (subscriptionIndex.length !== 1) {
            throw new Error(`Found an invalid number of subscriptions ${subscriptionIndex.length}`);
        }

        this._callbacks.splice(subscriptionIndex[0].index, 1);
    }

    notifySubscribers() {
        for (let i = 0; i < this._callbacks.length; i++) {
            const callback = this._callbacks[i].callback;
            callback();
        }
    }

    static get instance() { return authService }
}

const authService = new AuthorizeService();

export default authService;
