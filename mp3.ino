#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
 
const char* ssid     = "Junwoo";
const char* password = "00000000";


String pageMain= R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Emotion</title>
<style>
*{margin : 0; padding : 0; box-sizing : border-box; font-family: 'Poppins', sans-serif;}
body {display : flex; align-items: center; justify-content: center; min-height : 100vh; background: linear-gradient(#FD8D58, #DC611E)}
.wrapper{background : #f6f6f6; padding : 50px 30px; border-radius : 15px; max-width:350px; width : 80%; display:flex; align-items:center; flex-direction : column} 

.section .emojis{height : 500%; display : flex; flex-direction : column;}
.section .emojis li{list-style : none; height : 20%; width : 100%; transition : all 0.3s ease;}
.section .emojis li img{height : 80%; width: 100%;}
 
.wrapper .slider{height : 12px; width : 100%; background :#f6f6f6; margin-top : 40px; border-radius: 40px; position : relative;}
.wrapper .section {height : 150px ; width: 150px; overflow : hidden;}

.slider input{position : absolute; width: 100%; height : 100%; top: 0; outline : none; -webkit-appearance : none;}

.slider input::-webkit-slider-thumb{height : 25px; width:25px; -webkit-appearance : none; background : none; cursor: pointer;}

.slider .progess-bar{height : 90%; width : 0%; background : #DC611E ;border-radius: 50px; position : relative;}

.slider .thumb{height : 25px; width: 25px; background : #DC611E; border-radius :50%; position : absolute; top:50%; left :0%; z-index : 1; transform : translate(-50%, -50%); padding : 2px; pointer-events: none;}

.slider .thumb span{display : block; height : 100%; width : 100%; background: linear-gradient(#FD8D58, #DC611E); border : 2px solid #f6f6f6; border-radius : 50%;}  

</style>
</head>
<body>
<div class = "wrapper">
    <div class= "section">
        <div class = "emojis">
        <li class ="slide-icon"><img src ="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FbcjfQn%2FbtrQDEZ0oHj%2F2IVsb4SYjX5zX7HGlGcsk0%2Fimg.jpg"></li>
        <li><img src ="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FbbgrDA%2FbtrQDEseaN5%2F7B6XefK6tntZZJte4gccCk%2Fimg.jpg"></li>
        <li><img src ="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2Fn5Jkt%2FbtrQyXs6sjl%2FlyKbRkpkC6Xn85DM1Vjgbk%2Fimg.jpg"></li>
        <li><img src ="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FzLK2a%2FbtrQDPG9LGp%2FGFKa7r6p5kbVDmQxSC1QaK%2Fimg.jpg"></li>
        <li><img src ="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FtW2sx%2FbtrQDP1rXMR%2FBgv1e8onbiBAaQD1kP5f9k%2Fimg.jpg"></li>
        </div>
    </div>
    <div class = "slider">
        <input type = "range" min = "0" max = "100" value = "0">
        <div class = "thumb"><span></span></div>
        <div class = "progess-bar"></div>
    </div>
</div>

<script>     
    const slider = document.querySelector("input");
    const bar = document.querySelector(".progess-bar");
    const thumb = document.querySelector(".thumb");
    const slideIcon = document.querySelector(".slide-icon");
    const target = document.querySelector('body');
    const cursur = document.querySelector('.thumb span')
 
  var PopUp;

    slider.oninput = ()=>{
        let value = slider.value;
        thumb.style.left = value +'%';
        bar.style.width = value +'%';

        
        if (value < 20){
            slideIcon.style.marginTop = "0px";
            target.style.background='linear-gradient(#FD8D58, #DC611E)'
            bar.style.background ='linear-gradient(#FD8D58, #DC611E)'
            cursur.style.background = 'linear-gradient(#FD8D58, #DC611E)'
            thumb.style.background = 'linear-gradient(#FD8D58, #DC611E)' 
            sendData("Angry")
            openAngry();
            closeAngry();
         
        }
        if(40 > value && value >= 20){
            slideIcon.style.marginTop = "-150px";
            target.style.background = 'linear-gradient(#FD8D58, #dc9d1e)'
            bar.style.background ='linear-gradient(#FD8D58, #dc9d1e)'
            cursur.style.background = 'linear-gradient(#FD8D58, #dc9d1e)'
            thumb.style.background = 'linear-gradient(#FD8D58, #dc9d1e)'
            sendData("Upset")
            openUpset();
            closeUpset();
        }
        
        if(60 > value && value >= 40){
            slideIcon.style.marginTop = "-300px";
            target.style.background='linear-gradient(#fddc58, #dca91e)'
            bar.style.background ='linear-gradient(#fddc58, #dca91e)'
            cursur.style.background = 'linear-gradient(#fddc58, #dca91e)'
            thumb.style.background = 'linear-gradient(#fddc58, #dca91e)'
           //  data =60;
            sendData("SoSo")
            openSoSo();
            closeSoSo();
            
        }
        if(80 > value && value >= 60){
            slideIcon.style.marginTop = "-450px";
            target.style.background='linear-gradient(#dffd58, #c6dc1e)'
            bar.style.background ='linear-gradient(#dffd58, #c6dc1e)'
            cursur.style.background = 'linear-gradient(#dffd58, #c6dc1e)'
            thumb.style.background = 'linear-gradient(#dffd58, #c6dc1e)'
           //  data = 80;
           sendData("Good");
           openGood();
           closeGood();
           
        }
        if(100 >= value && value >= 80){
            slideIcon.style.marginTop = "-600px";
            target.style.background='linear-gradient(#cefd58, #9adc1e)'
            bar.style.background ='linear-gradient(#cefd58, #9adc1e)'
            cursur.style.background = 'linear-gradient(#cefd58, #9adc1e)'
            thumb.style.background = 'linear-gradient(#cefd58, #9adc1e)'
           // data = 100;
           sendData("VeryGood")
            openVeryGood();
            closeVeryGood();
        }

       function sendData(CMD){   // sendData 인자값 함수
         var xhttp = new XMLHttpRequest(); // Ajax 방식. URL으로 데이터 가져옴
         xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {  // 4 : 응답완료, status : 요청이 준비된 상태
          document.getElementById("text").innerHTML = xHttp.responseText // 문자열 반환
          }
          }  
        };

        function openAngry(){
          PopUp = window.open("/setPLAYER?PLAYERCMD=Angry");
        }
        
        function closeAngry(){
          PopUp.close();
        }

        function openUpset(){
          PopUp = window.open("/setPLAYER?PLAYERCMD=Upset");
        }
        
        function closeUpset(){
          PopUp.close();
        }

        function openSoSo(){
          PopUp = window.open("/setPLAYER?PLAYERCMD=SoSo");
        }

       function closeSoSo(){
          PopUp.close();
        }

        function openGood(){
          PopUp = window.open("/setPLAYER?PLAYERCMD=Good");
        }

       function closeGood(){
          PopUp.close();
        }

        function openVeryGood(){
          PopUp = window.open("/setPLAYER?PLAYERCMD=VeryGood");
        }

       function closeVeryGood(){
          PopUp.close();
        }

                        
     xhttp.open("GET", "setPLAYER?PLAYERCMD="+CMD,true);  // 내 아이피/setPLAYER?PLAYCMD=인자값 으로 요청 받아옴. (GET 방식)
     xhttp.send(); // URL으로 데이터 가져온거 전송
    }
</script>
</body>
</html>
)=====";

ESP8266WebServer server(80);
SoftwareSerial mySerial(D7, D8);



void handleMain() {
  String html = pageMain;
  server.send(200, "text/html", html);
}

void handlePLAYER1(){
 String PLAYERCMD = server.arg("PLAYERCMD"); // 피라미터
  Serial.println(PLAYERCMD);
  if(PLAYERCMD == "Angry") { // 피라미터가 Angry이면 음악 1 재생
    long randNumber1 = random(1,6);
    Serial.print(randNumber1);
    if (randNumber1 == 1){
      Serial.println(".이별택시 - 김연우");   
    }
    else if (randNumber1 == 2){
      Serial.println(".미쳐 - 포미닛");
    }
    else if (randNumber1 == 3){
      Serial.println(".바보처럼 - 2am");
    }
    else if (randNumber1 == 4){
      Serial.println(".Attention - NewJeans");      
    }
    else {Serial.println(".응급실 - izi");}
    
    mp3_play(randNumber1);
  } 
  if(PLAYERCMD == "Upset") { // 피라미터가 Upset이면 음악 2 재생
    long randNumber2 = random(6,11);
    Serial.print(randNumber2);
    if (randNumber2 == 6){
      Serial.println(".Don't Touch Me - 환불원정대");   
    }
    else if (randNumber2 == 7){
      Serial.println(".Shoot Out - 몬스터 엑스");
    }
    else if (randNumber2 == 8){
      Serial.println(".가시 - 버즈");
    }
    else if (randNumber2 == 9){
      Serial.println(".죽을만큼 아파서 - MC몽");      
    }
    else {Serial.println(".Day Day - 비와이");}
    mp3_play(randNumber2);
  }
  if(PLAYERCMD == "SoSo") { // 피라미터가 SoSo이면 음악 3 재생
    long randNumber3 = random(11,16);
    Serial.print(randNumber3);
    if (randNumber3 == 11){
      Serial.println(".살랑살랑 - 김란영");   
    }
    else if (randNumber3 == 12){
      Serial.println(".찹살떡 - 10cm, 하하");
    }
    else if (randNumber3 == 13){
      Serial.println(".지나오다- 닐로");
    }
    else if (randNumber3 == 14){
      Serial.println(".밝게 빛나는 별이 되어 비춰줄게 - 송이한");      
    }
    else {Serial.println(".Hype Boy - NewJeans");}
    mp3_play(randNumber3);
  }
  
  if(PLAYERCMD == "Good"){ // 피라미터가 Good 이면 음악 4 재생
    long randNumber4 = random(16,21);
    Serial.print(randNumber4);
    if (randNumber4 == 16){
      Serial.println(".볼빨간 사춘기 -여행");   
    }
    else if (randNumber4 == 17){
      Serial.println(".Cookie - NewJeans");
    }
    else if (randNumber4 == 18){
      Serial.println(".밤하늘의 별을 - 경서");
    }
    else if (randNumber4 == 19){
      Serial.println(".천태만상 - 윤수현");      
    }
    else {Serial.println(".Go High - 이영지");}
    mp3_play(randNumber4);
  }
  if(PLAYERCMD == "VeryGood"){ // 피라미터가 VeryGood 이면 음악 5 재생
    long randNumber5 = random(21,26);
    Serial.print(randNumber5);
    if (randNumber5 == 21){
      Serial.println(".상상더하기 - 라붐");   
    }
    else if (randNumber5 == 22){
      Serial.println(".Very Nice - SevenTeen");
    }
    else if (randNumber5 == 23){
      Serial.println(".Some - 소유,정기고");
    }
    else if (randNumber5 == 24){
      Serial.println(".우리의꿈 - 코요태");      
    }
    else {Serial.println(".SEXYBACK - 저스틴브레이크");}
    mp3_play(randNumber5); 
  }
}


void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");      
  }

  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleMain);
 
  server.begin();
  
  Serial.println("Server started");

   mySerial.begin (9600);
   mp3_set_serial (mySerial);    //set softwareSerial for DFPlayer-mini mp3 module 
   delay(1);                     // delay 1ms to set volume
   mp3_set_volume (30);          // value 0~30
   
   server.on("/setPLAYER", handlePLAYER1);  // 내 아이피 주소 + /setPLAYER + handPLAYER1 실행   
}
void loop()
{
  server.handleClient();  
}
