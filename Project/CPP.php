<?php
	ini_set("log_errors", false);
	ini_set('display_errors', 1);
	ini_set('display_startup_errors', 1);
	error_reporting(E_ALL);
	date_default_timezone_set("UTC");

	include_once dirname(__FILE__) . "/../../ProjectGen/ProjectGen.php";
	include_once dirname(__FILE__) . "/Core/CPP/Core.php";
	include_once dirname(__FILE__) . "/CLI/CPP/CLI.php";
	include_once dirname(__FILE__) . "/Test/CPP/Test.php";
	include_once dirname(__FILE__) . "/../../LangShared/LangShared.php";

	class Lang_Config extends Solution_Config
	{
		public function __construct($sAction)
		{
			parent::__construct($sAction);
			
			$this->m_pProjectArray[] = new Core_Config($sAction);
			$this->m_pProjectArray[] = new CLI_Config($sAction);
			$this->m_pProjectArray[] = new Test_Config($sAction);
			$this->m_pProjectArray[] = new LangShared_Config($sAction, dirname(__FILE__) . "/../LangShared.package-list", dirname(__FILE__) . "/../Transpiled/LangShared");
		}

		public function GetName() { return "Lang"; }
	}

	ProjectGen(new Lang_Config(ProjectGen_GetAction()));
?>
