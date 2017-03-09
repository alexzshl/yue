#!/usr/bin/env node

// Copyright 2017 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

const cp    = require('child_process')
const fs    = require('fs')
const path  = require('path')
const https = require('https')
const zlib  = require('zlib')

const {argv} = require('./common')

if (argv.length != 2) {
  console.error('Usage: download_node_headers runtime version')
  process.exit(1)
}

const runtime = argv[0]
const version = argv[1]

const prefix = {
  electron: 'https://gh-contractor-zcbenz.s3.amazonaws.com/atom-shell/dist',
  node: 'https://nodejs.org/dist',
}

if (!(runtime in prefix)) {
  console.error(`Unkown runtime: ${runtime}`)
  process.exit(2)
}

const node_dir = path.join('third_party', `node-${version}`)
if (fs.existsSync(node_dir)) {
  process.exit(0)
}

const url = `${prefix[runtime]}/${version}/node-${version}.tar.gz`
https.get(url, (response) => {
  response.pipe(zlib.createGunzip())
          .pipe(cp.exec('tar xf -', {cwd: 'third_party'}).stdin)

  // Download node.lib on Windows.
  if (process.platform == 'win32') {
    response.once('end', () => {
      downloadNodeLib('x64')
      downloadNodeLib('x86')
    })
  }
})

function downloadNodeLib(arch) {
  const lib = `${prefix[runtime]}/${version}/win-${arch}/node.lib`
  return https.get(lib, (response) => {
    const lib_dir = path.join(node_dir, arch)
    fs.mkdirSync(lib_dir)
    response.pipe(fs.createWriteStream(path.join(lib_dir, 'node.lib')))
  })
}