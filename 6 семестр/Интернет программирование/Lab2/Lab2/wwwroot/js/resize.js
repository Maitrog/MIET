setInterval(() => {
    if ($(window).width() < 700) {
        $('.leftCol').hide();
        $('.rightCol').hide();
        $('.centerCol').css('margin', '0 0 0 0');
    }
    else {
        $('.leftCol').css('display', 'flex');
        $('.rightCol').css('display', 'flex');
        $('.centerCol').css('margin', '0 180px 0 25%');
    }
});