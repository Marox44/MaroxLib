/*jshint browser: true, node: true, jquery: true*/

/** @namespace */
var Marox = {};

/**
 * Removes any duplicate elements from the array. Returns new array;
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

/**
 * Returns array containing mutual elements of two arrays
 * @param   {Array} array1 Array one
 * @param   {Array} array2 Array two
 * @returns {Array}
 */
Marox.mutualElements = function (array1, array2) {
	return $.grep(array1, function (element) {
		return $.inArray(element, array2) !== -1;
	});
};

/**
 * Returns array containing elements from array1 which are not in array2 (A\B)
 * @param   {Array} array1 Array A (elements to check for their existance in array2)
 * @param   {Array} array2 Array B
 * @returns {Array}
 */
Marox.differentElements = function (array1, array2) {
	return array1.filter(function (obj) {
		return array2.indexOf(obj) == -1;
	});
};

/**
 * Return parameters value from URL (like in PHP $_GET)
 * @param   {String} sParam Parameter name
 * @returns {String} Parameter value
 */
Marox.getUrlParameter = function (sParam) {
	var sPageURL = window.location.search.substring(1);
	var sURLVariables = sPageURL.split('&');
	for (var i = 0; i < sURLVariables.length; i++) {
		var sParameterName = sURLVariables[i].split('=');
		if (sParameterName[0] == sParam) {
			return sParameterName[1];
		}
	}
};
