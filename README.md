# Interactive Lighting & Data Collection with Arduino

![Rendering](https://github.com/nickkunz/cloudynight/blob/master/media/rendering.jpg)

## Executive Summary
Cloudy Night is an interactive lighting and data collecting prototype. The device was developed to provide illuminated feedback loops in low light conditions throughout the city while collecting unidentifiable data on its participants. The intent of the project was to assess if interactive lighting could enhance public park engagement and safety. 

The first deployment occurred on May 4th, 2019 at Starlight Park in the Bronx, New York. The stakeholders of the project were the Bronx River Alliance with special consideration given to the people and parks they serve. After a 3 hour deployment of the prototype in the afternoon and evening, the collected data was analyzed for quality, focusing on interpretability and inference. 

It was found that both directionality of human movement and the presence of children could be roughly approximated. The presence of children was used as a proxy for the perception of public safety, where it was assumed that mothers will not bring their children into environments that are perceived to be unsafe. 

Although this was assumed, and a rigorous analysis was not conducted to assess the number of occurrences of each event, it was more important that this project demonstrated that capturing these areas of interest was possible. It was determined that the Cloudy Night prototype was a useful device for creating interactive illuminances, while assessing rough approximations of public park safety and human movement through both directionality and the presence of children.

The project was implemented in Arduino. The code include here is intended for execution on the Arduino platform. The operational hardware used in this prototype was: Arduino Uno, SD Data Logger Shield for Arduino, Sparkfun Qwiic Shield for Arduino, Sparkfun Qwiic Connect Cables, SparkFun Human Presence Sensor Breakout, Adafruit 12mm Diffused Thin Digital RGB LED Pixels (Strand of 25).

This work was completed with Shuyang Huang and Shiori Osakata in partial fulfillment for the course Urban Informatics II at Columbia University GSAPP in 2019. A video of the making of Cloudy Night can be found <a href="https://www.youtube.com/watch?v=UFdZAbp3dc4&t=0s">here</a>.

## Concept
![Sketch](https://github.com/nickkunz/cloudynight/blob/master/media/sketch.png)
![Interactivity](https://github.com/nickkunz/cloudynight/blob/master/media/interaction.png)

## Realization 
![Concept](https://github.com/nickkunz/cloudynight/blob/master/media/concept.png)
![Implementation1](https://github.com/nickkunz/cloudynight/blob/master/media/implementation1.png)

## Process & Technology
![Sensor Detail](https://github.com/nickkunz/cloudynight/blob/master/media/sensordetail.jpg)
![Microcontroller Stack](https://github.com/nickkunz/cloudynight/blob/master/media/stack.jpg)
![LED Lights](https://github.com/nickkunz/cloudynight/blob/master/media/leds.jpg)
![Tech Schematic](https://github.com/nickkunz/cloudynight/blob/master/media/schematic.jpg)
![Cloud](https://github.com/nickkunz/cloudynight/blob/master/media/cloud.jpg)

## Implementation
![Implementation0](https://github.com/nickkunz/cloudynight/blob/master/media/implementation.jpeg)
![Implementation2](https://github.com/nickkunz/cloudynight/blob/master/media/implementation2.jpg)

## Data Collection
![Plot1](https://github.com/nickkunz/cloudynight/blob/master/media/humanplot.jpg)
![Plot2](https://github.com/nickkunz/cloudynight/blob/master/media/directionplot.jpg)
![Plot3](https://github.com/nickkunz/cloudynight/blob/master/media/childrenplot.jpg)
