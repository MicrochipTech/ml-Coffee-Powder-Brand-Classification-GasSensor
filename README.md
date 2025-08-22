![Coffee Bean Classifier](./coffee_ml_banner.png)

# ☕ Coffee Bean Classifier – Gas Sensing + Embedded ML  

This project demonstrates how **embedded machine learning** can be used to classify different coffee brands using **gas sensing technology**. By leveraging the **BME688 4-in-1 environmental sensor** and **Microchip’s PIC32CX-BZ2 / WBZ451 microcontrollers**, we built a complete workflow from **data collection → model training → deployment on hardware**.  

The project highlights how **low-cost sensors** and **TinyML techniques** can be applied to real-world use cases such as **food authentication, air quality monitoring, and industrial predictive maintenance**.  

---

## 🔎 Project Summary
- **Problem:** Coffee authenticity and quality control is often expensive and requires lab-grade instruments.  
- **Solution:** Use gas sensor readings (VOC signatures) + embedded ML to classify coffee brands in real time.  
- **Approach:**  
  1. Capture sensor data from different coffee brands.  
  2. Train an ML classifier using Microchip’s MPLAB ML Development Suite.  
  3. Deploy the model on a low-power PIC32CX-BZ2 MCU for on-device inference.  

---

## 🛠️ Hardware Setup
- **2 × PIC32CX-BZ2 / WBZ451 Curiosity Boards**  
  - One board + **BME688 sensor** inside a sealed jar with coffee (sensor node).  
  - Second board connected to PC via USB (host node).  
- **BME688 Environmental Sensor** – measures temperature, humidity, pressure, and gas resistance.  
- **3.7V Li-Po Battery Pack** – powers the sensor node for portable operation.  

---

## 📂 Repository Contents


---

## 📊 Data Collection & Training
- Warm up sensor for **20 minutes** before recording.  
- Capture **30-minute sessions** for each coffee brand.  
- Use **MPLAB Data Collector** to log sensor data.  
- Import datasets into **ML Model Builder** for training.  
- **AutoML pipeline** used to find optimal features + model.  
- Best model achieved **~93% accuracy**, with small memory footprint (<20 KB).  

---

## 🤖 Deployment
- Exported model as a **Knowledge Pack**.  
- Integrated into MCU firmware with simple API calls (`init_model()`, `predict()`).  
- Flashed onto PIC32CX-BZ2 board using MPLAB X IDE.  
- Real-time predictions streamed to PC via **MPLAB Data Visualizer**.  

---

## 🎥 Demo Workflow


*(Insert block diagram or screenshot of live MPLAB Visualizer output)*  

---

## 🌟 Key Features
- Fully embedded ML workflow (no cloud dependency).  
- Works on **resource-constrained MCUs**.  
- Portable, battery-powered setup.  
- Generalizable to multiple applications:  
  - Food authentication (spices, tea, wine).  
  - Environmental monitoring (indoor air quality, VOC detection).  
  - Industrial gas sensing and predictive maintenance.  
  - Healthcare (VOC-based breath diagnostics).  

---

## 📜 License
Microchip Technology Inc License – free to use, modify, and distribute.  

