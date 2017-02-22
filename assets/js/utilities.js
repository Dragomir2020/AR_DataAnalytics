var getUrlParameter = function getUrlParameter(sParam) {
    var sPageURL = decodeURIComponent(window.location.search.substring(1)),
        sURLVariables = sPageURL.split('&'),
        sParameterName,
        i;

    for (i = 0; i < sURLVariables.length; i++) {
        sParameterName = sURLVariables[i].split('=');

        if (sParameterName[0] === sParam) {
            return sParameterName[1] === undefined ? true : sParameterName[1];
        }
    }
};

function getDevice(device_name) {
    console.log("getDevice: " + device_name);
    $.ajax({
        url: "/api/device/" + device_name,
        dataType: "json", 
        success: function(data) {
            console.log(data);
            $('.device-pk').append(data.pk);
        },
        error: function(errorCode) {
            console.log(errorCode);
        }
    });
};