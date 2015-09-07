/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
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

//app.initialize();

$("#search").on("keyup",function() {
    var value = $(this).val().toLowerCase().trim();

    $("#tabSongs tr").each(function(index) {
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
});

var fs=null;

// device APIs are available
    function onDeviceReady() {
            alert("device ready");
            var i=2;
            $("#coverContainer").text("Ricerca automatica del server in corso...");
            while(i<20&&indirizzo=="172.20.10.") {
                findServer(indirizzo+i);
                i++;
            }
            //Not fired setIP so, manually insert
            $("#coverContainer").html('<p>La ricerca sta impiegando troppo tempo!<br>Potrebbe essere necessario inserire manualmente indirizzo del Server</p><center><form><h1>Inserimento Indirizzo Server</h1>Inserire indirizzo del Server nel formato XXX.XXX.XXX.XXX: <input type="text" id="textIP"><input type="submit" value="Imposta"></form></center>');
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
    function onRequestFileSystem(fileSystem) {
        console.log("Richiesta FS");
        fs = fileSystem;
        basepath="";
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
        //var i=0;
        //for (i=0;i<extensionAccepted.length;i++) {
            if(endpart==extensionAccepted) {
                console.log("Quindi restituisco true");
                return true;
            }
        //}
        return false;
    }

    /*function uploadFiles (readedFile) {
        console.log("nella funzione di loading del file");
        // Steps:
        // 1) Upload the file to server
        // 2) Send to server file name
        // 3) Send ever second alive message to server and receive possibly data
                    // Server Steps:
                    // 1) Create new pointer riproduttore to play the song
                    // 2) Save older pointer status and pause it
                    // 3) Replace old with new pointer
                    // 4) If song ended send to client the signal (Maybe sameway of index.html webmanager)
        // 5) Check ever 500ms if the streaming device is connected. If False replace new pointer with newer and renable web and device controlùù
        $.ajax({
            url: indirizzo+'/filesUploader.php?callback=?&files',
            type: 'POST',
            data: readedFile,
            xhr: function() {
                myXhr = $.ajaxSettings.xhr();
                if(myXhr.upload) {
                    myXhr.upload.addEventListener('progress',progressHandlingFunction, false);
                }
                return myXhr;
            }
            cache: false,
            dataType: 'jsonp',
            processData: false, // Don't process the files
            contentType: false, // Set content type to false as jQuery will tell the server its a query string request
            success: function(data, textStatus, jqXHR)
            {
                if(typeof data.error === 'undefined')
                {
                    // Success so call function to process the form
                    //submitForm(event, data);
                    console.log("File caricato correttamente. Informo il server. (newSong)")
                    $.get(indirizzo+"worker.php?callback=?", {
                        port: "7777",
                        application: "3",
                        priority:"0",
                        message: "newSong"});
                }
                else
                {
                    // Handle errors here
                    // console.log('ERRORS: ' + data.error);
                }
            },
            error: function(jqXHR, textStatus, errorThrown)
            {
                // Handle errors here
                console.log('ERRORS: ' + textStatus);
                // STOP LOADING SPINNER
            }
        });
    }*/
    var data;
    function readFile(event){
        console.log("Nella funzione readFile");
        var entry;
        try{
            fs.root.getFile(event.data.filecorrente, {create: false, exclusive:false}, function (fileEntry) {
            console.log("fileEntry");
            fileEntry.file(function (file) {
                /*if(isNullOrUndefined(file)){
                    console.log("file null");
                    return;
                    }*/
                    fileReader = new FileReader();
                    fileReader.onload = shipOff;
                    fileReader.onloadend = function (e) {
                        console.log("Read completed.");
                        console.log(e);
                        //uploadFiles(file);
                    };

                    fileReader.onloadstart = function (e) {
                        console.log("Read start");
                        console.log(e);
                    };

                    fileReader.onerror = function (e) {
                        console.log(e);
                        console.log("Read error.");
                    };

                    fileReader.readAsBinaryString(file);
                }, function (e) {
                    console.error("Read Failed");
                });
            }, function (e) {
                console.log("read error");
            });
        }catch(error){
            console.log(error);
            console.error("Read Error occurred");
        }
    }
    function shipOff(event) {
        var result=event.target.result;
        console.log("ShipOff");
        console.log(event);
        $.post(indirizzo+'/filesUploader.php?callback=?', {data: result},function (data) {
            console.log(data);
        });
    }
    var basepath;
    var entries;
    function onReadEntries(entries) {
        console.log("onReadEntries -> Siamo entrati");
        var i;
        $("#labelTheadDir").text("");
        for (i = 0; i < entries.length; i++) {
           if (entries[i].isFile == true&&isAudio(entries[i].name)==true) {
             console.log("Canzone trovata!");
             console.log(entries[i]);
             $("#tabSongs > tbody").append('<tr><td>'+entries[i].name+'</td><td><button type="button" class="btn btn-default"><span class="glyphicon glyphicon-play">Play</span></button></td></tr>');
             var tempfile=entries[i].fullPath;
             console.log("Path completa:"+tempfile);
             $("#tabSongs button:last").click({filecorrente: tempfile},readFile);
             /*($("#tabSongs button:last")).click(function() {
                console.log("Usando la fullPath:"+tempfile);
                console.log("Nome entries:"+entries[i].name);
                readFile(tempfile);
             });*/
           }

           if (entries[i].isDirectory == true) {
            console.log("Directory trovata");
            console.log(entries[i]);
            $("#tabSongs > tbody").append('<tr><td>'+entries[i].name+'</td><td><button type="button" class="btn btn-default"><span class="glyphicon">Apri</span></button></td></tr>');
            $("#tabSongs button:last").click({valori: entries,attuale: i},bindButtonFolders);
           }
        }
        $("#tabSongs > tbody").append('<tr><td>Vai alla cartella superiore -> </td><td><button type="button" class="btn btn-default"><span class="glyphicon">Sali di un livello</span></button></td></tr>');
        $("#tabSongs button:last").click(function() {
            var prev; var count;
            console.log("basepath="+basepath);
            for (i=0;i<basepath.length;i++) {
                if (basepath[i]=="/"){
                    count++;
                }
            }
            count--;
            var newpath;
            for (i=0;i<basepath.length;i++) {
                if (count>=0) {
                    newpath[i]=basepath[i];
                    if (basepath[i]=="/") count--;
                }
            }
            basepath=newpath;
            $("#tabSongs > tbody").html("");
            if (basepath=='undefined') basepath="/";
            console.log("new basepath="+basepath);
            var directoryReader = basepath.createReader();
            directoryReader.readEntries(onReadEntries, errorHandler);
        });
    }
    function bindButtonFolders(event) {
        console.log(event);
        //console.log(event.data.valori[event.data.attuale.value]);
        alert(event.data.valori[event.data.attuale]);
        //console.log("Log della funzione usando name:"+event.data.valori[event.data.attuale.value].name);
        $("#tabSongs > tbody").html("");
        basepath=basepath+"/"+event.data.valori[event.data.attuale].name;
        var directoryReader = event.data.valori[event.data.attuale].createReader();
        directoryReader.readEntries(onReadEntries, errorHandler);
    }

        var indirizzo="172.20.10.";
        var find=0;
            function setServerIP(ip) {
                //if (find==0) {
                    indirizzo=ip;
                    find=1;
                    //$("#coverContainer").text("Trovato il server all'indirizzo "+indirizzo+", Benvenuto!");
                    console.log("Trovato il server all'indirizzo "+indirizzo+". Benvenuto!");
                    $("#coverContainer").hide();
                    $(".navbar-nav").show(); $(".navbar-toggle").show();
                    window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onRequestFileSystem, errorHandler);
                //}
            }
            function findServer(serverip) {
                $.ajax({
                    method:"GET",
                    url:"http://"+serverip+"/consoleWEB/worker.php",
                    data:{port: "7777", application: "3", priority:"0", message:"hello"},
                    dataType: "JSONP",
                    async: false,
                    success: function(data) {
                        if (data.value=="0afa2d1d877998a438089be1487aedb6") {
                            setServerIP("http://"+serverip+"/consoleWEB/")
                        }
                        else {console.log("founded IP "+serverip+" but ignored(not application)");}
                    }
                  }).fail(function() {
                    console.log("Problemi nella risoluzione dell'host "+serverip);
                  });
            }
