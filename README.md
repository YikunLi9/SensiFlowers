# SensiFlowers

## What the project does?

This project is an indoor artwork that connects with the environment and presents the data to the user in the form of art. The product will collect temperature and humidity of indoor environment through DTH-22 sensor, and display the data using the mechanical flower opening degree and color temperature of rgb light effect.

The whole product consists of three mechanical flowers and a wooden structure, as shown below:

<div align="center">
  <img src="https://github.com/YikunLi9/SensiFlowers/assets/146266229/c51adbdc-b03e-4da1-a81a-b77fee12efe2" alt="SensiFlowers">
</div>

The color of each flower in working mode represents a different data environment, with green representing carbon dioxide, red representing temperature, and blue representing humidity. As the ambient value increases, the color temperature will change from light to dark, and the flowers will gradually change from crouching to fully open.

## Why the project is useful?

We designed this project to fill a gap in the artistic emotional value of environmental monitors currently on the market. Most of the environmental data measurement devices on the market, only through a simple digital way, will measure the environmental data to express, which may lack a spiritual aesthetic, difficult to bring users a spiritual level of pleasure. 

Therefore, this product completes the measurement and display of environmental data through the artistic expression form of mechanical flower and lamp effect, and has a certain physical significance and practical value at the same time, it can also be used as an art decoration, placed in the living room or hung on the wall, bringing certain aesthetic value.

## How We Design？

### Initial Concept and Prototyping
The initial design concept focused on integrating natural elements, specifically using the imagery of a blooming flower to represent and interact with environmental data. Initial prototypes utilized thermally responsive metals to simulate the blooming process. However, this approach was found to interfere with the accurate monitoring of environmental conditions, as the device's primary function was compromised by the temperature sensitivity of the materials.

### Shift to Origami Modelling
To achieve a more reliable and aesthetically pleasing design, the development shifted towards origami modeling. This approach aimed to abstractly and artistically replicate the dynamic nature of a blooming flower, enhancing both visual appeal and functional reliability. Initial attempts to implement a hinged mechanism for transformation proved too complex and fragile for practical application.

<div align=center>
  <img src="https://github.com/YikunLi9/SensiFlowers/assets/146334863/024231f5-e3e3-42ef-bd44-bc0947ec2c36" alt="Shift to Origami Modelling" width="400">
</div>

### Material Innovation
The design evolved through a focus on material innovation. By integrating wooden panels with elastic TPU materials, the device was endowed with the necessary flexibility to mimic origami's bending and folding capabilities without compromising durability. This combination allowed significant bending angles while maintaining a robust structure within each modular unit.

<div align=center>
  <img src="/Doc/folding_animation.gif" alt="Material Innovation" width="400">
</div>

### Development of the Operational Mechanism
The operational mechanism was inspired by classic gear transmission systems, transforming rotational motion into linear motion. This design utilized widely available motors to drive the expansion and contraction of the flower-like structures from multiple angles, achieving a single motor-driven mechanism that allowed each unit to expand and contract based on pre-designed parameters.

<div align=center>
  <img src="/Doc/animation_05.gif" alt="Development of the Operational Mechanism" width="400">
</div>


### Enclosure Design
The final stage involved designing an enclosure to house and integrate the individual units while concealing sensors and electrical components. Laser-cut wooden panels were used to create a harmonious geometric arrangement that not only supports the structural integrity but also complements the aesthetic value of the device.

<div align=center>
  <img src="/Doc/pic3.png" alt="Enclosure Design" width="400">
</div>
## How this project works?

The project operates on data from the following sensors：

| Environment Data             | Sensor |
| ---------------------------- | ------ |
| Temperature & Humidity       | DHT22  |
| Carbon Dioxide Concentration | MQ135  |

And we set different ranges for these three environmental data to control the opening and closing of the mechanical flowers:

| Environment Data  | Upper Threshold of Optimal Range | Lower Threshold of Optimal Range |
| ----------------- | -------------------------------- | -------------------------------- |
| Temperature       | 30                               | 20                               |
| Humidity          | 80                               | 30                               |
| CO2 Concentration | 1000                             | 350                              |

The mechanical flowers will fully open or close when the values exceed or fall below these thresholds. Simultaneously, the color temperature of the LEDs will vary within the following range:

| Environment Data  | Base Colour | Upper Threshold (RGB) | Lower Threshold (RGB) |
| ----------------- | ----------- | --------------------- | --------------------- |
| Temperature       | Red         | 255, 0, 0             | 255, 50, 0            |
| Humidity          | Blue        | 0, 0, 255             | 80, 80, 255           |
| CO2 Concentration | Green       | 0, 255, 0             | 0, 255, 50            |




## How users can get started with the project?

The use of this product is very simple, you only need to plug the power cord into the socket and turn on the power supply. The processing and measurement of the data is carried out locally, without any network connection, and the user does not need to perform any assembly and other operations. Environmental data can be read from the color and openness of flowers.

## Team members & Product help

A total of 4 team members completed the development of this product. Yuhang Lei completed the basic concept design of the product and the task assignment of the team, and undertook the welding task in the assembly process. Yikun Li compiled and debugged the development code of the single chip computer program, and gave guiding opinions on the form of data expression. Tianming Liu completed the design of the mechanical flower gear transmission group, and completed the 3d modeling and cutting of the gear group and the wooden shape. Zhouyu Jiang is responsible for the spraying of mechanical flower surface paint and hardware assembly, in addition to market research and follow-up product service research.

If you have further inquiries about our product and services or other aspects, you can communicate with any team member through github private message to get detailed information or answers. The detail of product services would be talked later in this read.me file.
