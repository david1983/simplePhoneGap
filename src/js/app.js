 angular
     .module('myWeather', ['ngMaterial'])
     .controller('mainCtrl',function($scope, $http, $mdSidenav, $interval){

        $scope.defaultHost = 'davideandreazzini.co.uk:3999';  
        $scope.active = 'home'
         $scope.links = [
             {name: 'Home', href: '/'},{name: 'About', href: '/about'}
          ]

         $scope.sidenavToggle = function(){
              $mdSidenav('left').toggle()                
         }
         
         $scope.goTo = function(pagename){
             $scope.active = pagename;
            $mdSidenav('left').close();
         }

         $scope.getData = function(){
             $scope.loadData = true;
             $http.get('http://' + $scope.defaultHost)
                .then(function(result){
                    $scope.data = result.data;
                    $scope.loadData = false;
                }).catch(function(e){
                    $scope.error = e;
                });
         }

        
        $scope.retry = function(){
            $scope.count = 0;
            $scope.connectionError = false;
        }

        $scope.count = 0;
          $interval(function(){
                $scope.count++;
                if(!$scope.data && $scope.count>2) {                 
                    $scope.connectionError = true
                    return;
                } 
                $scope.getData()
            },5000);
         $scope.getData();

    })
    
 