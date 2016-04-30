$(document).ready(  //Dès que le document est prêt, on lance ce qui est en dessous
 function() 
 {
var Moment = moment();  //On charge la méthode princiupale de Moment.js
Moment.locale('fr');    //On règle la langue de la date en français au cas où
var Jour = Moment.format("D");//On récupère le jour précédent
var Mois = Moment.format("MM"); //On récupère le mois
var Annee = Moment.format("Y"); //On récupère l'année
var FormatFichier = Jour + '_' + Mois + '_' + Annee + '.xml';   //On concatène le tout en une variable qui correspond au nom du fichier d'hier


$.ajax( {   //On va chercher le fichier grâce à AJAX
            type: "GET",
            url: FormatFichier, //Le nom de fichier est fourni par la variable "FormatFichier"
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