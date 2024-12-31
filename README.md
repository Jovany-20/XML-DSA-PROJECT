# XML Editor and Visualizer

<div id="header" align="center">
  <img src="https://github.com/user-attachments/assets/72e4e9b2-d684-4c8a-91a9-ab3f7623adae" alt="header-image">
</div>

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Command Line Interface (CLI)](#command-line-interface-cli)
- [Commands Overview](#commands-overview)
- [Support](#support)

---

## Introduction
This project extends the functionality of an XML processing tool to provide advanced operations, including validation, correction, data transformation, visualization, and network analysis. The tool is designed to help developers and analysts work with XML files efficiently by combining essential features like beautifying, error correction, and data conversion with advanced capabilities like social network visualization and analysis.

## Features

- **XML Validation**: Detect and fix issues like mismatched or missing tags.
- **Formatting**: Prettify XML with proper indentation for readability.
- **XML to JSON Conversion**: Transform XML data into JSON for web applications.
- **Minification**: Reduce XML file size by removing unnecessary spaces and newlines.
- **Compression**: Compress XML files into a custom format to save space.
- **Decompression**: Restore compressed XML files to their original format.
- **Visualization**: Represent social networks as graphs.
- **Network Analysis**: Identify influencers, mutual connections, and follow suggestions.
- **Post Search**: Search posts by word or topic.

---

### **Command Line Interface (CLI)**
Perform quick and efficient operations on XML files via the CLI using the `.bat` script provided, `xml_editor`:
```bash
./xml_editor [command] -i [input_file] -o [output_file]
```
> [!TIP]
> Replace `[command]` with one of the available commands listed [below](#commands-overview).

--- 

## **Commands Overview**
The following is a comprehensive list of commands available in the XML Editor and example usage for each:

| Command        | Description                                       | Example Command                                              |
|----------------|---------------------------------------------------|--------------------------------------------------------------|
| `verify`       | Validate an XML file and optionally fix it.       | `./xml_editor verify -i input_file.xml -o output_file.xml`  |
| `format`       | Prettify an XML file for readability.             | `./xml_editor format -i input_file.xml -o output_file.xml` |
| `json`         | Convert XML to JSON format.                       | `./xml_editor json -i input_file.xml -o output_file.json`     |
| `mini`         | Minify XML by removing unnecessary spaces.        | `./xml_editor mini -i input_file.xml -o output_file.xml`    |
| `compress`     | Compress an XML file into a custom format.        | `./xml_editor compress -i input_file.xml -o output_file.comp` |
| `decompress`   | Restore compressed XML to its original form.      | `./xml_editor decompress -i input_file.comp -o output_file.xml` |
| `draw`         | Draw XML data as a graph.                         | `./xml_editor draw -i input_file.xml -o output_file.jpg`       |
| `most_active`  | Find the most active user in the XML data.        | `./xml_editor most_active -i input_file.xml`             |
| `most_influencer` | Find the most influential user in the XML data.| `./xml_editor most_influencer -i input_file.xml`         |
| `mutual`       | Find mutual users for given user IDs.              | `./xml_editor mutual -i input_file.xml -ids 1,2,3`       |
| `suggest`      | Suggest users for a given user ID.                | `./xml_editor suggest -i input_file.xml -id 1`           |
| `search`       | Search posts by word or topic.                    | `./xml_editor search -w word -t topic -i input_file.xml  ` |


---

## **Support**

If you encounter any issues or have questions about this project:  
1. **Raise an Issue**: Create an issue in the [GitHub repository](https://github.com/Jovany-20/XML-DSA-PROJECT/issues).  
3. **Explore Discussions**: Join discussions and check FAQs in the repository's Discussions tab.

Your feedback and suggestions are always welcome! 😊
