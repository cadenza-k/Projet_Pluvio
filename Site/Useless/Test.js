var Moment = moment();
Moment.locale('fr');
var Jour = Moment.subtract(1, 'Days').format("D");
var Mois = Moment.format("MM");
var Annee = Moment.format("Y");
var FormatFichier = Jour + '_' + Mois + '_' + Annee + '.xml';
alert(FormatFichier);