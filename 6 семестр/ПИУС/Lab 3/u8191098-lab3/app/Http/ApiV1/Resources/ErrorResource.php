<?php

namespace App\Http\ApiV1\Resources;

use Illuminate\Http\Resources\Json\JsonResource;

class ErrorResource extends JsonResource
{
    public function toArray($request)
    {
        return [
            'error' => [
                'code' => $this->code,
                'message' => $this->message,
                'meta' => $this->meta,
            ],
        ];
    }
}
