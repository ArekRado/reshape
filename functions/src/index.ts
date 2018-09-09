import * as functions from 'firebase-functions'
import * as express from 'express'
import * as cors from 'cors'

const app = express()

// Automatically allow cross-origin requests
app.use(cors({ origin: true }))

// Add middleware to authenticate requests
// app.use(myMiddleware);

// build multiple CRUD interfaces:
app.get('/collect', (req, res) => {
  res.send({ xd: 'xD' })
})

// Expose Express API as a single Cloud Function:
exports.widgets = functions.https.onRequest(app)
