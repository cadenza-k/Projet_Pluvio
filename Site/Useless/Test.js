$(document).ready(
function($)
{
var table = $('<table></table>').addClass('foo');
    
    for(i=0; i<3; i++)
    {    
    var row = $('<tr></tr>').addClass('bar').text('result ' + i);
    table.append(row);
    }

$('#here_table').append(table);

});



