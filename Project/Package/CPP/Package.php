<?php
	class Package_Config extends Project_Config
	{	
		public function __construct($sAction, $sAllowedDirectoryArray = array())
		{
			parent::__construct($sAction);

			// $sRegex = "/\.h$|\.c$/";
			// if ($this->m_sAction == ACTION_IOS_XCODE || $this->m_sAction == ACTION_WINDOWS_VS2008)
			//	$sRegex = "/\.h$|\.c$|\.m$/";

			$sRegex = "/\.hpp$|\.cpp$/";
			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__) . "/../../../../LangShared", $sRegex, $sAllowedDirectoryArray);
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
