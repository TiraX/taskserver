rem set DEBUG=shaderlib:* & npm start

supervisor --debug -i public/ -w db,routes,views,app.js,config.json ./bin/www