console.log('start test cluster !!');

const cluster = require('cluster');
const numCPUs = require('os').cpus().length;

if (cluster.isMaster) {
  console.log('  total cpu : [%d].', numCPUs);
  // Fork workers.
  for (var i = 0; i < numCPUs; i++) {
    cluster.fork();
  }

  cluster.on('exit', (worker, code, signal) => {
    console.log('worker [%d] died', worker.process.pid);
  });
} else {
  console.log(' ... ');
}
console.log('attention end..');