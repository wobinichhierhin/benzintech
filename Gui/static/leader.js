$(document).ready(function () {
    if ($LOCALE=="de_DE"){
                $(".en").show();
                $(".de").hide();
            }
    else if ($LOCALE=="en_US"){
                $(".en").hide();
                $(".de").show();
    };

})

function change_locale(locale_to_set) {
    console.log(locale_to_set);
    $.post($SCRIPT_ROOT + '/change_locale',{
        locale: locale_to_set,
    });
}