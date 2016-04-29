$(document).ready(
 function() 
 {
var d = new Date();
var month = d.getMonth()+1;
var day = d.getDate();
var horodatage = d.getFullYear() + '_' + (('' + month).length<2 ? '0' : '') + month + '_' + (('' + day).length<2 ? '0' : '') + day;
var XMLFichier = 


$.ajax( {
            type: "GET",
            url: "Pluvio.xml",
            dataType: "xml",
            success: function(xml) 
                     {
                       $(xml).find('heure').each(   
                         function()
                         {
                            var id = $(this).attr('id');
                            var data = $(this).find('data').text();
                            $('<div class="items" id="link_' + id + '"></div>').html('<p>à ' + id +  'heure, il a plu ' + data + ' millimètres</p>').appendTo('#Div_XML');
                         });
                      }
        });
 });