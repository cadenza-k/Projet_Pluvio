$(document).ready(  //Dès que le document est prêt, on lance ce qui est en dessous
 function() 
 {
var M = moment();  //On charge la méthode princiupale de Moment.js
M.locale('fr');    //On règle la langue de la date en français au cas où
var Jour = M.format("D");//On récupère le jour précédent
var Mois = M.format("MM"); //On récupère le mois
var Annee = M.format("Y"); //On récupère l'année
var FormatFichier = Jour + '_' + Mois + '_' + Annee + '.xml';   //On concatène le tout en une variable qui correspond au nom du fichier d'hier
var Data = 0;


$.ajax( {   //On va chercher le fichier grâce à AJAX
            type: "GET",
            url: FormatFichier, //Le nom de fichier est fourni par la variable "FormatFichier"
            dataType: "xml",
            success: function(xml) 
                {
                    $(xml).find('heure').each( //pour chaque duo de baslises <heure>,  
                    function()
                    {
                        var id = $(this).attr('id'); //Récupérer l'arrtibut ID
                        var data = $(this).find('data').text(); //Récupérer la valeur contenue entre les balises <data>
                        Data= Data + parseInt(data); //On additione les données entre-elles
                        $("#Pluvio > tbody:last").append('<tr><td>' + id + ' h</td><td>' + data + 'mm</td></tr>');
                    });
                    $("#Pluvio > tbody:last").append('<tr style="background-color: #ffffcc;"><td>TOTAL</td><td>' + Data + 'mm</td></tr>');
                }
        });
 });