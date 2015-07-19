/*jshint browser: true, node: true, jquery: true*/

/** @namespace */
var Marox = {};

/**
 * Removes any duplicate elements from the array
 * @param   {Array} list Source array
 * @returns {Array}
 */
Marox.unique = function (list) {
	var result = [];
	$.each(list, function (i, e) {
		if ($.inArray(e, result) == -1) result.push(e);
	});
	return result;
};

Marox.mutualElements = function (array1, array2) {
	return $.grep(array1, function (element) {
		return $.inArray(element, array2) !== -1;
	});
}

Marox.differentElements = function (array1, array2) {
	return array1.filter(function (obj) {
		return array2.indexOf(obj) == -1;
	});
}

Marox.getUrlParameter = function (sParam) {
	var sPageURL = window.location.search.substring(1);
	var sURLVariables = sPageURL.split('&');
	for (var i = 0; i < sURLVariables.length; i++) {
		var sParameterName = sURLVariables[i].split('=');
		if (sParameterName[0] == sParam) {
			return sParameterName[1];
		}
	}
}
