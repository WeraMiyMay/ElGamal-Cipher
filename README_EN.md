# ElGamal Cipher (VCL/C++ Builder)

This project provides an implementation of the **ElGamal public‑key cryptosystem** written in **C++ (C++ Builder / VCL)**.  
The application allows you to:

- generate ElGamal system parameters;
- encrypt text using the ElGamal algorithm;
- decrypt previously encrypted text;
- view the resulting (a, b) pairs and decrypted output.

---

## ⚙️ Algorithm Overview

The program implements the classical **ElGamal encryption scheme** over the multiplicative group modulo a large prime number *p*.

### Parameters:

- **p** — large prime  
- **g** — primitive root modulo p  
- **X** — private key  
- **Y = g^X mod p** — public key  
- **k** — random ephemeral session key used during encryption

### Encryption

Each character is converted to a numeric value:  
`m = charToValue(ch)`

For every character, the algorithm produces a pair:

```
a = g^k mod p
b = m * (Y^k mod p) mod p
```

### Decryption

```
M = b * a^(p−1−X) mod p
```

---

## 📂 Project Structure

File | Description
---- | -----------
`Unit8.cpp` | Core implementation of ElGamal encryption/decryption
`Unit8.h` | Form and function declarations
VCL Form UI | User interface, input/output fields, buttons

---

## 🚀 Features

- Manual or automatic input of p and g  
- Secure random generation of k, X, and Y  
- Text encryption into ElGamal pairs  
- Text decryption from encrypted pairs  
- Cyrillic character support (`а`–`я`)  
- Validity checks for key parameters  
- Clear visualization of each encryption stage  

---

## ▶️ How to Use

### 1. Enter parameters:
- **p** — a large prime  
- **g** — a primitive root modulo p  

### 2. Click **Generate Keys** (`Button3`)

This generates:

- `k` — ephemeral session key  
- `X` — private key  
- `Y` — public key  

### 3. Enter text to encrypt (Memo1)

### 4. Click **Encrypt** (`Button1`)

Encrypted pairs `(a, b)` will appear in Memo2.

### 5. Click **Decrypt** (`Button2`)

The decrypted text will appear in Memo3.

---

## 📌 Limitations

- Supports only Cyrillic letters (`а`–`я`).
- p must be prime; g must be a primitive root.
- This is an **educational implementation** and should not be used for real cryptographic security.

---

## 🧠 Technologies

- C++ Builder / VCL  
- Modular arithmetic  
- Fast modular exponentiation  

---

## 📝 License

This project is free to use and modify for educational purposes.

---

## 🌍 Multilingual README

If this file is saved as `README_EN.md`, you can link between languages:

**In `README.md`:**

```
[English Version](README_EN.md)
```

**In `README_EN.md`:**

```
[Русская версия](README.md)
```

Yes — GitHub will correctly show both files in the repository.

---

