<?php
	class Test_Config extends Project_Config
	{
		public function __construct($sAction)
		{
			parent::__construct($sAction);

			$this->m_xFileArray = array_merge(
				ProjectGen_ParseDirectory(dirname(__FILE__) . "/../../../Transpiled/Test", "/\.hpp|\.cpp/"),
				ProjectGen_ParseDirectory(dirname(__FILE__), "/\.hpp$|\.cpp$/"));
		}

		public function GetName() { return "Test"; }
		public function GetKind() { return KIND_CONSOLE_APP; }
		public function GetBaseDirectory() { return dirname(__FILE__); }

		public function GetIncludeDirectoryArray($sConfiguration, $sArchitecture)
		{
			return array(
				//"../Core",
			//	"../ThirdParty",
				//"../Package",
			);
		}

		public function GetLinkFlags($sConfiguration, $sArchitecture)
		{
			if ($this->m_sAction == ACTION_EMSCRIPTEN_GMAKE)
				return "-s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1"; // tests run through interperator, so we can sleep and stuff wating for worker callbacks
			if ($this->m_sAction == ACTION_OSX_GMAKE)
				return "-framework OpenGL -framework AudioUnit -framework CoreAudio -framework AudioToolbox -framework CoreFoundation -framework ApplicationServices -framework IOKit -framework AppKit"; // -L/usr/local/lib -L/usr/local/opt/curl/lib 
			if ($this->m_sAction == ACTION_LINUX_GMAKE)
				return "-ldl";
			return "";
		}

		public function GetDependancyArray()
		{
			$sArray = array(
				//"Core",
			//	"ThirdParty",
				//"Package",

			//	"Engine", // hax for split packagge
			//	"EngineJob",
			//	"ThirdParty",
				"Core",
			//	"ServerCore",
			);

			return $sArray;
		}
	}
?>