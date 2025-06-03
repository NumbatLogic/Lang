pipeline{
	agent { label "Linux" }
	stages{
		stage("Checkout"){
			steps{
				cleanWs()
				dir("Lang"){
					checkout([$class: 'GitSCM',
					branches: [[name: '*/main']],
					doGenerateSubmoduleConfigurations: false,
					extensions: [[$class: 'SubmoduleOption',
					disableSubmodules: false,
					parentCredentials: false,
					recursiveSubmodules: true,
					reference: '',
					trackingSubmodules: false]], 
					submoduleCfg: [], 
					userRemoteConfigs: [[url: 'https://github.com/NumbatLogic/Lang']]])
				}
				dir("ProjectGen"){
					git url: "https://github.com/NumbatLogic/ProjectGen",
						branch: "main",
						credentialsId: 'c532651f-f9a2-48a8-8a37-8df46a9c5ee2'
				}
			}
		}

		stage("Build"){
			steps{
				sh "cd Lang && ./CIRebuild.sh"
			}
		}

		stage("Log Parse"){
			steps{
				logParser ([
					projectRulePath: 'Lang/LogParsingRules',
					parsingRulesPath: '',
					showGraphs: true, 
					unstableOnWarning: true, 
					useProjectRule: true
				])
			}
		}
	}
}