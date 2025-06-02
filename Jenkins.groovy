pipeline{
	agent { label "Linux" }
	stages{
		stage("Checkout"){
			steps{
				cleanWs()
				dir("Lang"){
					git url: "https://github.com/NumbatLogic/Lang",
						branch: "main",
						credentialsId: 'c532651f-f9a2-48a8-8a37-8df46a9c5ee2'
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
	}
}