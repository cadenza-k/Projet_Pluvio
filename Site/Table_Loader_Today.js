$(document).ready(
 function() 
 {
var Moment = moment();
Moment.locale('fr');
var Jour = Moment.format("D");
var Mois = Moment.format("MM");
var Annee = Moment.format("Y");
var FormatFichier = Jour + '_' + Mois + '_' + Annee + '.xml';
//alert(FormatFichier);


$.ajax( {
            type: "GET",
            url: FormatFichier,
            dataType: "xml",
            success: function(xml) 
                     {
                       $(xml).find('heure').each(   
                         function()
                         {
                            var id = $(this).attr('id');
                            var data = $(this).find('data').text();
                            $('<div class="items" id="link"></div>').html('<tr><td>' + id + '</td><td>' + data + '</td></tr>').appendTo("#Pluvio > tbody:last");
                         });
                      }
        });
 });