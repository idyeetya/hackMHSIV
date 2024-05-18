const express = require('express');
const app = express()
const port = 3000


app.use(express.urlencoded({extended: true}));

// Parse JSON bodies (as sent by API clients)
app.use(express.json());


app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})


// Access the parse results as request.body
    app.post('/', function(request, response){
        const f_intercept = (request.body.FreqPlMn);
        const f_scale = (request.body.FreqScale);
        const max = (request.body.Max);
        const d_intercept = (request.body.DelayPlMn);
        const d_scale = (request.body.DelayScale);

        console.log(f_intercept);
        console.log(f_scale);
        console.log(max);
        console.log(d_intercept);
        console.log(d_scale);

        const execSync = require('child_process').execSync;

        // Pass the variables to the Bash script as arguments
        const command = `bash b_script.bash ${d_intercept} ${f_intercept} ${d_scale} ${f_scale} ${max}`;
        
        const output = execSync(command, { encoding: 'utf-8' });  // the default is 'buffer'
        console.log('Output was:\n', output);
    });