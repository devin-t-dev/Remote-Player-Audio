	function ottieniCanzoni() {
		$("#tabSongs > tbody").html("");
		$.getJSON("worker.php", {
			port: "7777",
			application: "2",
			message:"songs"}
			).done(function(data) {
			$.each(data.value,function(i,item) {
				$("#tabSongs > tbody").append('<tr><td id="song-'+i+'">'+item.name+'</td><td><button type="button" class="btn btn-default"><span class="glyphicon glyphicon-play"></span></button></td></tr>');
				($("#tabSongs button:last")).click(function() {
					$.get("worker.php", {port: "7777", application: "2", message: "set"+i});
				});
			});
			$("#coverContainer").hide();
		}).fail(serverOffline);
	}

	$(document).ready(function(){
		ottieniCanzoni();
	});

	$("#prevButton").click(function() {
		$.get( "worker.php", { port: "7777", application: "2", message:"prev" }
		).done(function(data) {
			/*$("#canzoneAttuale").text($("#song-"+data.value).text());*/
		});
	});
	$("#playButton").click(function() {
		$.get( "worker.php", { port: "7777", application: "2", message:"playPause" } ); //Prev Server Action
		$("playButton").toggleClass("glyphicon-play");
		$("playButton").toggleClass("glyphicon-pause");
	});
	$("#nextButton").click(function() {
		$.getJSON( "worker.php", { port: "7777", application: "2", message:"skip" }
			).done(function(data) {/*$("#canzoneAttuale").text($("#song-"+data.value).text());*/});
	});
var first=false;
function killApp() {
	$.ajax({
		method:"GET",
		url:"worker.php",
		data:{port:"7777",application: "2", message:"killStreaming"},
		dataType: "JSON",
		success: function(data) {}
	});
}
function serverOffline() {
    $("#canzoneAttuale").text("Server Audio non disponibile =(");
   	ottieniCanzoni();
   	first=true;
   	$("#coverContainer").html('<p><h1>Ops!</h1></p><p>Si e verificato un problema nel ricevimento dei dati dal server. Sei sicuro che sia raggiungibile?</p>');
	$("#coverContainer").show();
}

(function worker() {
  $.ajax({
  	method:"GET",
    url:'worker.php',
    data:{port: "7777", application: "2", message:"getPuntatore"},
    dataType: "JSON",
    success: function(data) {
      if (data.value=="appAttiva")
      {
      	$("#coverContainer").show();
      	$("#coverContainer").html("<center><h1>Riproduzione da Applicazione Attiva</h1><br> Vuoi ripristinare la Riproduzione da dispositivo di massa esterno? <br><input type='button' onclick='killApp()' value='SI'></center>");
      } else {
      	if (first) {ottieniCanzoni(); first=false;}
      	$("#canzoneAttuale").text($("#song-"+data.value).text());
      }
    },
    complete: function() {
      // Schedule the next request when the current one's complete
      setTimeout(worker, 1200);
    }
  }).fail(serverOffline);;
})();

/*$("#search").on("keyup",function() {
	var value = $(this).val().toLowerCase().trim();

	$("table tr").each(function(index) {
		if (index !== 0) {
			$row=$(this);
			var song=$row.find("td:first()").text().toLowerCase().trim();
			if ((song.indexOf(value)>=0)||value=="") {
				$row.show();
			} else {
				$row.hide();
			}
		}
	});
});*/
