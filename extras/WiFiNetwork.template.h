const char WN_Connect_Page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body {padding: 0 20px;}
    .form {display: flex; flex-direction: column; width: 100%;}
    .form input, .form select {box-sizing: border-box;}
    .form .input-text {width: 100%; padding:10px; border-radius: 10px; border: 2px solid gray;}
    .form .input-submit {cursor: pointer; background-color: #ff9100; color: #FFF; font-weight: bold; width: 100%; padding:10px; border-radius: 10px; border: 0 none;}
    .form .select {width:25%; padding:5px; border-radius: 10px; border: 2px solid gray;}
    .form .form-block {position:relative; margin: 10px 0; display: flex; flex-direction: row; justify-content: space-between; align-items: center;}
    .view-button {position:absolute; right:15px; top: 8px; cursor: pointer; width: 24px; height: 24px; background-size: contain; background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAAA7AAAAOwBeShxvQAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAAI2SURBVFiF5dfLb01RFMfxTzHQagVtlIpBCTERA2kMqAShHn+COWnSiUgMBE0k979g4JEQY4MODEg8BuIPQAxEB2hFVEndvgz2PunJdfa5t4+4g65k5+Tux/qetc9v7bVvi+bYRjxCe7PgLzCPkf8N34BnEf4yvszqgT9dSXg7+nA6tj5pQeW/+bLgO3AdbzAbHebbbBy7hp64pmMl4NtxG9UCaKpVcXe58LW4golFgItaKbwl0b8VD3A8Mf4Nj/EBc9iLs+iqmfdK0MgENuN76kXydgijiqOZxlW0Fqxbj4riyCv4HH2X2klMJuDVGA1B8UO4h1u4iG7F3/xmzsckTqXg5zCVgM/HyOEAPhWMzyQir503hTO18KP4XQIfF7a9IwEv2vbhknm/cCSD74qAMiXfiXOHGoQT0rDM5zh61whq76zdkhp7H58pEeXVnkX2to7PTjxcV2dSZnPx+acOvIKdeI41DfrWq/FPcEF62zPBDcbf9+v4HIts0K9chGNCnncrV/tHofK1CYdVmQgP1+5EvTSsKM7zPHx/7LtR4mfKwnnyjx1T/+zPw/sFtQ/GyLNAphNrf+JECp5Z2VFcVljaYuQp+KiCLEoVoy5BRAO5vrzah7Eb7wS17xGK0ZaEvyc4j6+J8ULbhC8aO15T7QcuC6V9UZa6QDYKrwqXmG2LBZfBW3FJuFxmqZhvM3gtFK0eS7RGr85t2CdcWAZw0EIWLNmafm9fnXDCH8SmwQmlc6RZ8L9wKFCOCtXHxwAAAABJRU5ErkJggg==);}
    .view-button.active {background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAABFQAAARUBKX4CGwAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAAFuSURBVFiF7ZaxbsIwEIY/hy5dGTKWCZU5U5+ic96BhSFv0icoqpRKSAx9gw5InboxlG4dssDARBlA16GOZFJjJ5UiZ+Ckk5L49/2/fReflYgQ0qKg7BcBXRBw1QSslFLADXBrOMCH4V/SpLJFxOvAEHgEdoB4fKexw1qxPcQj4Ak41CCu+kHPHTUWAPSAB+D4D+KqH3Wsno1LVdOllLoGnoF7R+Y+gTfgXb8nwJ1O1Tl7AVIR+T75Wll5H1g4VrMHMiCy7Fqkx/aO+Qugb00BEANLD3lSo2ATj4glENsEzB2TBMgM7ADIgUJ7DgyM8cwTa34iAEg9E1bltmvyrQWzLUXodKw8MdOy/mJg7QFPjdXlDlxu4KaemGvNzcwDFGBiBC4cuMLATWrEnQXvBREwBjYeXGI8vzpw5lhyFvVrG2Acvgg78Rt24iAKdRR3qxmFaMfdvJBYhLR2JftTAy5r41LaSEAb1olecBEQ1H4AL783rHcg0wcAAAAASUVORK5CYII=);}
    .hidden {display: none !important;}
    .block-title {text-align: center;}
  </style>
</head>
<body>
  <h3 class="block-title">WiFi Networks</h3>
  <form class="form" action="/save-credits" method="POST">
    <div class="form-block">
      <input class="input-text" type="text" placeholder="SSID" name="ssid" />
    </div>
    <div class="form-block">
      <label>Security</label>
      <select class="select" onChange="togglePasswordInput(this)" name="security">
        <option value="0" selected="selected">None</option>
        <option value="1">Yes</option>
      </select>
    </div>
    <div class="form-block hidden" data-password-container>
      <input class="input-text" type="password" placeholder="Password" name="pass" />
      <i class="view-button" onclick="togglePasswordView(this)"></i>
    </div>
    <div class="form-block">
      <input class="input-submit" type="submit" value="Try connect" />
    </div>
  </form>
  <h3 class="block-title">WiFi Settings</h3>
  <form class="form" action="/reset" method="POST">
      <input class="input-submit" type="submit" value="Reset settings" />
  </form>
  <script>
    var password_container = document.querySelector('[data-password-container]');
    function togglePasswordInput(select) {
      var option = select.options[select.selectedIndex];
      if (parseInt(option.value)) {
        password_container.classList.remove("hidden");  
      } else {
        password_container.classList.add("hidden");  
      }
    }

    function togglePasswordView(icon) {
      var password_input = password_container.querySelector('input[name="pass"]');
      if (password_input.type == 'password') {
        password_input.type = 'text';
        icon.classList.add('active');
      } else {
        password_input.type = 'password';
        icon.classList.remove('active');
      }
    }
  </script>
</body>
</html>)rawliteral";