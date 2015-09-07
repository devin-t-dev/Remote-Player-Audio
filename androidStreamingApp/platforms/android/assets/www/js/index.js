/**
 * Devin Taietta
 * Progetto Player Audio
 */
//var baseIP="172.20.10.";
var baseIP="192.168.43.";
var indirizzo=baseIP;
//var $find=0;
var fs=null;
var application="3";
var socketPort="7777";
var indexOfSongsDir=-1; var numSongs=0;
//var $pauseWorker=0;
var app = {
    // Application Constructor
    initialize: function() {
        this.bindEvents();
    },
    // Bind Event Listeners
    //
    // Bind any events that are required on startup. Common events are:
    // 'load', 'deviceready', 'offline', and 'online'.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    // deviceready Event Handler
    //
    // The scope of 'this' is the event. In order to call the 'receivedEvent'
    // function, we must explicitly call 'app.receivedEvent(...);'
    onDeviceReady: function() {
        app.receivedEvent('deviceready');
    },
    // Update DOM on a Received Event
    receivedEvent: function(id) {
        onDeviceReady();
    }
};

// device APIs are available
    function onDeviceReady() {
            console.log("Dispositivo Pronto.");
            var i=2;
            $("#coverContainer").text("Ricerca automatica del server in corso...");
            while(i<224&&indirizzo==baseIP&&($("#find").val()=="0")) { //!
                findServer(indirizzo+i);
                console.log($("#find").val());
                i++;
            }
            //Not fired setIP so, manually insert
            $("#coverContainer").html('<p>La ricerca sta impiegando troppo tempo!<br>Potrebbe essere necessario inserire manualmente indirizzo del Server</p><center><form><h1>Inserimento Indirizzo Server</h1>Inserire indirizzo del Server nel formato XXX.XXX.XXX.XXX: <input type="text" id="textIP"><input type="submit" onclick="setServerIP('+$("#textIP").val()+')" value="Imposta"></form></center>');
    }

    function serverOffline() {
        console.log("Problemi nella risoluzione dell'host "+indirizzo);
        $("#canzoneAttuale").text("Server Audio non raggiungibile =(");
        $("#coverContainer").text('Ricerca del Server in corso...'); $("#coverContainer").show();
        $("#container").hide(); $(".navbar-nav").hide(); $(".navbar-toggle").hide();
        $("#pauseWorker").val("0");
    }

    function setServerIP(ip) {
        indirizzo=ip;
        $("#find").val("1");
        console.log("Trovato il server all'indirizzo "+indirizzo+". Benvenuto!");
        $("#coverContainer").hide();
        $("#container").show();
        $(".navbar-nav").show(); $(".navbar-toggle").show();
        window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onRequestFileSystem, errorHandler);
    }
    function findServer(serverip) {
        if ($("#find").val()=="0") {
            $.ajax({
                method:"GET",
                url:"http://"+serverip+"/consoleWEB/worker.php",
                data:{port: "7777", application: application, message:"hello"},
                dataType: "JSONP",
                success: function(data) {
                    if (data.value=="0afa2d1d877998a438089be1487aedb6") {
                        setServerIP("http://"+serverip+"/consoleWEB/")
                    }
                }
                }).fail(function() {
                    console.log("Client Non raggiungibile: "+serverip);
                });
            }
        }

    function onRequestFileSystem(fileSystem) {
        console.log("Richiesta FS");
        fs = fileSystem;
        console.log(fs);
        var directoryReader = fs.root.createReader();
        directoryReader.readEntries(onReadEntries, errorHandler);
    }

    function isAudio (filename) {
        var extensionAccepted=".mp3";
        var len=filename.length;
        console.log(filename+" len:"+len);
        var endpart=filename[len-4]+filename[len-3]+filename[len-2]+filename[len-1];
        console.log("extension rilevata:"+endpart);
        if(endpart==extensionAccepted) {
            return true;
        }
        return false;
    }

    function readFile(event) {
        console.log(event);
        $("#pauseWorker").val("1");
        indexOfSongsDir=event.data.posizione;
        var success = function (r) {
            console.log("Code:"+r.responseCode);
            console.log("Response:"+r.response);
            console.log("Sent:"+r.bytesSent);
            $.ajax({
                method:"GET",
                url:indirizzo+"worker.php?callback=?",
                data:{port: socketPort, application: application, message:"newStreamSong"},
                dataType: "JSONP",
                success: function(data) {
                    console.log(data);
                },
                complete: function() {
                    $("#canzoneAttuale").text("Caricamento effettuato");
                    $.ajax({
                        method:"GET",
                        url:indirizzo+"worker.php?callback=?",
                        data:{port: socketPort, application: application, message:"forcePlay"},
                        dataType: "JSONP",
                        success: function(data) {
                            console.log(data);
                        }
                    }).fail(serverOffline);
                    $("#pauseWorker").val("0");
                } // end complete function
            }).fail(serverOffline); //end Ajax
        }
        var fail = function(error) {
            console.log("Upload error "+error.code);
            console.log("source:"+error.source);
            console.log("dest:"+error.target);
            alert("Errore nel caricamento della canzone!!");
            $.ajax({
                method:"GET",
                url:indirizzo+"worker.php?callback=?",
                data:{port: socketPort, application: application, message:"quittingStream"},
                dataType: "JSONP",
                success: function(data) {
                    console.log(data);
                }
            }).fail(serverOffline);
        }
        $("#canzoneAttuale").text("Caricamento in corso ...");
        $.ajax({
            method:"GET",
            url:indirizzo+"worker.php?callback=?",
            data:{port: socketPort, application: application, message:"startLoading"},
            dataType: "JSONP",
            async:false,
            success: function(data) {
                console.log(data);
            }
        }).fail(serverOffline);
        var options=new FileUploadOptions();
        options.filekey = "file";
        options.fileName = event.data.nomefile;
        options.mimeType = "audio/mpeg3";
        options.chunkedMode = false;
        //options.headers = { Connection: "close"};
        var ft= new FileTransfer();
        ft.onprogress = function(progressEvent) {
            if (progressEvent.lengthComputable) {
                var perc = Math.floor(progressEvent.loaded / progressEvent.total * 100);
                $("#canzoneAttuale").text(perc + "% Caricato...");
            } else {
                $("#canzoneAttuale").text($("canzoneAttuale").text()+".");
            }
        };
        ft.upload(event.data.filecorrente,encodeURI(indirizzo+"filesUploader.php"), success, fail, options);
    }

    var basepath=null;
    var entries;
    function onReadEntries(entries) {
        console.log("onReadEntries -> Siamo entrati");
        var i; var j=0;
        indexOfSongsDir=0;
        for (i = 0; i < entries.length; i++) {
           if (entries[i].isFile == true&&isAudio(entries[i].name)==true) {
             console.log("Canzone trovata!");
             console.log(entries[i]);
             $("#tabSongs > tbody").append('<tr><td id="songName'+j+'">'+entries[i].name+'</td><td><button type="button" class="btn btn-default" id="songBtn'+j+'""><span class="glyphicon glyphicon-play">Play</span></button></td></tr>');
             $("#tabSongs button:last").click({filecorrente: entries[i].toURL(),nomefile:entries[i].name, posizione:j},readFile);
             j++;
           }

           if (entries[i].isDirectory == true) {
            console.log("Directory trovata");
            console.log(entries[i]);
            $("#tabSongs > tbody").append('<tr><td>'+entries[i].name+'</td><td><button type="button" class="btn btn-default" id="file'+i+'"><span class="glyphicon">Seleziona</span></button></td></tr>');
            $("#tabSongs button:last").click({valori: entries,attuale: i},bindButtonFolders);
           }
        }
        numSongs=j;
        //$("#tabSongs > tbody").append('<tr><td>Vai alla cartella superiore -> </td><td><button type="button" class="btn btn-default" id="btnUpDir"><span class="glyphicon">Sali di un livello</span></button></td></tr>');
        /*$("#btnUpDir").click(function() {
            $("#tabSongs > tbody").html("");
            if (basepath=='undefined'||basepath==''||basepath==null) basepath=fs.root;
            console.log("new basepath");
            console.log(basepath); alert(basepath);
            var directoryReader = basepath.createReader();
            directoryReader.readEntries(onReadEntries, errorHandler);
        });*/
    }
    function bindButtonFolders(event) {
        console.log(event);
        //console.log(event.data.valori[event.data.attuale.value]);
        //console.log("Log della funzione usando name:"+event.data.valori[event.data.attuale.value].name);
        $("#tabSongs > tbody").html("");
        event.data.valori[event.data.attuale].getParent(function () {
            console.log("Parent Name"+parent.name);
            basepath=parent;
            console.log("VALORE BASEPATH:");
            console.log(basepath);
        },errorHandler);
        var directoryReader = event.data.valori[event.data.attuale].createReader();
        directoryReader.readEntries(onReadEntries, errorHandler);
    }

    function errorHandler(e) {
      var msg = '';

      switch (e.code) {
        case FileError.QUOTA_EXCEEDED_ERR:
          msg = 'QUOTA_EXCEEDED_ERR';
          break;
        case FileError.NOT_FOUND_ERR:
          msg = 'NOT_FOUND_ERR';
          break;
        case FileError.SECURITY_ERR:
          msg = 'SECURITY_ERR';
          break;
        case FileError.INVALID_MODIFICATION_ERR:
          msg = 'INVALID_MODIFICATION_ERR';
          break;
        case FileError.INVALID_STATE_ERR:
          msg = 'INVALID_STATE_ERR';
          break;
        default:
          msg = 'Unknown Error';
          break;
      };

      console.log('Error: ' + msg);
      alert('Error: '+msg);
    }
function prevSong() {
    console.log("Previus song requested");
    indexOfSongsDir--;
    console.log(indexOfSongsDir);
    if (indexOfSongsDir>0)
        $("#songBtn"+indexOfSongsDir).trigger("click");
}
function playPause() {
    console.log("playPause pressed");
    $.get(indirizzo+"worker.php", { port: socketPort, application: "2", message:"playPause" } ); //trick we use the same function in App 2
    $("playButton").toggleClass("glyphicon-play");
    $("playButton").toggleClass("glyphicon-pause");
}
function nextSong() {
    console.log("Next song requested");
    indexOfSongsDir++;
    console.log(indexOfSongsDir);
    if (indexOfSongsDir<numSongs)
        $("#songBtn"+indexOfSongsDir).trigger( "click" );
    else
        {indexOfSongsDir=0;
        $("#songBtn"+indexOfSongsDir).trigger( "click" );}
}
//Check if song is ended
(function worker() {
    if ($("#pauseWorker").val()=="0") {
      $.ajax({
        method:"GET",
        url:indirizzo+'worker.php?callback=?',
        data:{port: socketPort, application: application, message:"getStreamStatus"},
        dataType: "JSONP",
        success: function(data) {
          if (data.value=="nextSongRequired") {
            nextSong();
          }
        $("#coverContainer").hide();$("#container").show(); $(".navbar-nav").show(); $(".navbar-toggle").show();
        $("#canzoneAttuale").text($("#songName"+indexOfSongsDir).text());
        },
        complete: function() {
          // Schedule the next request when the current one's complete
          setTimeout(worker, 1000);
        }
      }).fail(serverOffline);//end fail
    } else {
        setTimeout(worker,2000);
    } //end if
})();

$("#ricerca").on("keyup",function() {
    var value = $(this).val().toLowerCase().trim();
    console.log("Ricerca di testo "+value);
    $("table tr").each(function(index) {
        if (index !== 0) {
            $row=$(this);
            console.log($row);
            var song=$row.find("td:first()").text().toLowerCase().trim();
            if ((song.indexOf(value)>=0)||value=="") {
                $row.show();
            } else {
                $row.hide();
            }
        } else console.log("index 0");
    });
});
