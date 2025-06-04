<?php
	class Package_Config extends Project_Config
	{	
		public function __construct($sAction)
		{
			parent::__construct($sAction);
			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__) . "/../../../../LangShared/Assert", "/\.hpp|\.cpp/");
		}

		public function GetName() { return "Package"; }
		public function GetKind() { return KIND_STATIC_LIBRARY; }
		public function GetBaseDirectory() { return dirname(__FILE__); }

		public function GetIncludeDirectoryArray($sConfiguration, $sArchitecture)
		{
			$sArray = array(
				//"../Package",
				//"../ThirdParty",
			);
			return $sArray;
		}

		public function GetDependancyArray()
		{
			$sArray = array(
				//"Shared",
				//"ThirdParty",
			);

			return $sArray;
		}
	}
?>
