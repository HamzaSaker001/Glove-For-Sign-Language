# 🤟 Glove for Deaf — Sign Language Translator

A real-time wearable assistive device that reads hand gestures via flexible sensors and translates them into readable text on an LCD. Built to bridge communication between deaf individuals and those unfamiliar with sign language.

---

## 📌 Project Overview

Deaf individuals rely on sign language to communicate, but most people around them don't understand it. This glove-based device detects the posture of all five fingers using flexible sensors and maps each unique gesture to a word, which is then displayed on an LCD screen in real time — no sign language knowledge required from the reader.

---

## ✨ Features

- 🖐️ **5 flexible sensors** — one per finger for full hand posture detection
- 💬 **15+ sign language words** translated to text
- 📟 **Real-time LCD display** — old word clears automatically when a new gesture is detected
- ⚡ **Fast response** — near-instant gesture recognition
- 🔋 **Standalone wearable** — no external computer required

---

## 🗂️ System Architecture

```
  Thumb Sensor  ──ADC(0)──┐
  Index Sensor  ──ADC(1)──┤
  Middle Sensor ──ADC(2)──┼──► ATmega32 MCU ──► LCD Display
  Ring Sensor   ──ADC(3)──┤         │
  Pinky Sensor  ──ADC(4)──┘         └──► Gesture Lookup Table
                                          (15+ words mapped)
```

---

## ⚙️ How It Works

1. Each flexible sensor changes resistance based on finger bend angle
2. The MCU reads analog voltage from each sensor via ADC
3. The combination of all 5 finger states forms a unique "posture code"
4. The posture code is matched against a lookup table of 15+ gestures
5. The corresponding word is printed on the LCD
6. When a new valid gesture is detected, the previous word is cleared

### Example Gesture Mapping

| Gesture (Finger States) | Word Displayed |
|---|---|
| All fingers extended | `HELLO` |
| Thumb + Index only | `YES` |
| All fingers closed (fist) | `NO` |
| Index + Middle extended | `PEACE` |
| Thumb only | `GOOD` |
| ... | ... (15+ total) |

---

## 🧰 Components

| Component | Quantity | Purpose |
|---|---|---|
| Microcontroller (ATmega32) | 1 | Main processing |
| Flexible Sensor | 5 | One per finger |
| LCD (16x2 Character) | 1 | Text output display |
| Glove | 1 | Wearable mounting base |
| Connecting Wires | — | Sensor to MCU routing |
| Resistors (voltage divider) | 5 | ADC signal conditioning |
| Battery / Power Supply | 1 | Portable power |

---

## 🔌 Interfaces Used

- **ADC (5 channels)** — Reading flexible sensor voltages
- **GPIO** — LCD control (4-bit or 8-bit mode)

---

## 🛠️ Tools & Environment

- **Language:** Embedded C
- **MCU:** ATmega32 (AVR)
- **Build:** Hardware only (no simulation — real wearable)
- **Programmer:** AVRDUDE / USBasp

---

## 🔭 Future Improvements

- [ ] Add audio output (text-to-speech module)
- [ ] Expand gesture library to 50+ words
- [ ] Add Bluetooth to send text to a smartphone
- [ ] Replace LCD with OLED for compact form factor
- [ ] Machine learning-based gesture recognition for higher accuracy

---

## 👥 Team

Project built as part of the **Embedded Systems Diploma** at AMIT Learning.
Team size: up to 3 members.

---

## 📄 License

This project is for educational purposes.
