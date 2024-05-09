# Clock in C++ using MVC architecture

The code is in C++ as `clock.cpp` 

* `main()` sets up the model, view, and controller
* Controller holds a `Clock` object
* Clock holds a `Time` Model object
* Time is delivered to `Display` as View object


## Runing the code

```bash
g++ clock.cpp -o clock
./clock
```

[Link to Google Colab notebook](https://colab.research.google.com/drive/1Wi6Oxl1q_yKlB2IIhmeXwUr2uZGfeAH8?usp=sharing)
