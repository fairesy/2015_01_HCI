import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import ddf.minim.spi.*; 
import ddf.minim.signals.*; 
import ddf.minim.*; 
import ddf.minim.analysis.*; 
import ddf.minim.ugens.*; 
import ddf.minim.effects.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class launchpad extends PApplet {










Serial inputPort;  // Create object from Serial class
String inputString;

Minim minim;
AudioPlayer player00, player01, player02,player03,player04,player05,player06,player07,player08,player09, player10, player11, player12, player13,player14,player15;

public void setup() 
{
  size(600, 600);
  frameRate(30);
  println(Serial.list());
  String portName = Serial.list()[5];
  inputPort = new Serial(this, portName, 9600);
  inputPort.bufferUntil('\n');

  //load sound files
  minim = new Minim(this);
  player00 = minim.loadFile("00.wav");
  player01 = minim.loadFile("01.wav");
  player02 = minim.loadFile("02.wav");
  player03 = minim.loadFile("03.wav");
  player04 = minim.loadFile("04.wav");
  player05 = minim.loadFile("05.wav");
  player06 = minim.loadFile("06.wav");
  player07 = minim.loadFile("07.wav");
  player08 = minim.loadFile("08.wav");
  player09 = minim.loadFile("09.wav");
  player10 = minim.loadFile("10.wav");
  player11 = minim.loadFile("11.wav");
  player12 = minim.loadFile("12.wav");
  player13 = minim.loadFile("13.wav");
//  player14 = minim.loadFile("14.wav");
//  player15 = minim.loadFile("15.wav");
}

public void draw()
{
  if(inputString != null){
    String result = inputString.replaceAll("[\n\r]", "");   
    
    if(result.equals("0")){
      player00.play();
    }else if(result.equals("1")){
      player01.play();
    }else if(result.equals("2")){
      player02.play();
    }else if(result.equals("3")){
      player03.play();
    }else if(result.equals("4")){
      player04.play();
    }else if(result.equals("5")){
      player05.play();
    }else if(result.equals("6")){
      player06.play();
    }else if(result.equals("7")){
      player07.play();
    }else if(result.equals("8")){
      player08.play();
    }else if(result.equals("9")){
      player09.play();
    }else if(result.equals("10")){
      player10.play();
    }else if(result.equals("11")){
      player11.play();
    }else if(result.equals("12")){
      player12.play();
    }else if(result.equals("13")){
      player13.play();
    }else if(result.equals("14")){
//      player14.play();
    }else if(result.equals("15")){
//      player15.play();
    }
  }
}

public void serialEvent(Serial inputPort){
  inputString = inputPort.readString();
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--full-screen", "--bgcolor=#666666", "--stop-color=#cccccc", "launchpad" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
