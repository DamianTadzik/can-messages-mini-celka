# CAN Messages - Mini Celka 

## Description
This is project that defines signals transmitted over the CAN(```can_messages_mini_celka.dbc```).

Based on this ```.dbc``` file the ```cmmc.c``` and ```cmmc.h``` sources are generated with python and cantools, they can be included later in any embedded project.

Next, based on the previously generated files the ```cmmc_decoder.mex``` is generated, it can be used for efficient decoding of the can frames in the ```.m``` scripts.


### Detailed description of the common C sources generation based on ```.dbc```
1. Launch the python enviromet ```source venv/Scripts/activate```
2. Run the ```generate.sh``` script?
3. Run ```python -m cantools generate_c_source --use-float --database-name src/cmmc can_messages_mini_celka.dbc```



## Requirements
- Python 3.8
- Matlab2018b+



### First ever launch of python enviroment:
1. Install appropriate version of Python, and navigate to the repo
2. Run the ```python -m venv venv```
3. Activate the enviroment ```source venv/Scripts/activate```
4. Installation of the packages ```pip install cantools```
5. When all packages are installed save requirements with ```pip freeze > requirements.txt```

### Launching the enviroment after cloning or moving to a new machine:
1. Install appropriate version of Python, and navigate to the repo
2. Run the ```python -m venv venv```
3. Activate the enviroment ```source venv/Scripts/activate```
4. Install the packages ```pip install -r requirements.txt```



## Useful resources:
- [CSS Electronics DBC editor online](https://www.csselectronics.com/pages/dbc-editor-can-bus-database)
- []()
- []()
