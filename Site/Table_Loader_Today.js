$(document).ready(  //Dès que le document est prêt, on lance ce qui est en dessous
 function() 
 {
var Moment = moment();  //On charge la méthode princiupale de Moment.js
Moment.locale('fr');    //On règle la langue de la date en français au cas où
var Jour = Moment.format("D");//On récupère le jour précédent
var Mois = Moment.format("MM"); //On récupère le mois
var Annee = Moment.format("Y"); //On récupère l'année
var FormatFichier = Jour + '_' + Mois + '_' + Annee + '.xml';   //On concatène le tout en une variable qui correspond au nom du fichier d'hier
var Data = 0;


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
                             Data= Data + parseInt(data);
                            $("#Pluvio > tbody:last").append('<tr><td>' + id + '</td><td>' + data + 'mm</td></tr>');
                         });
                         $("#Pluvio > tbody:last").append('<tr style="background-color: #ffffcc;"><td>TOTAL</td><td>' + Data + 'mm</td></tr>');
                      }
        });
 });