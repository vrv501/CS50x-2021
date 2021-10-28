function myFunction() {
    let y = document.getElementsByTagName("ul");
    if (y[0].className == "nav_menu")
      y[0].className = "nav_menu responsive";
    else
      y[0].className = "nav_menu";
  }
